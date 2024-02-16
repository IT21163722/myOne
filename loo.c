#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

int main() {
    av_register_all();

    AVFormatContext *formatContext = avformat_alloc_context();
    if (avformat_open_input(&formatContext, "input_video.mp4", NULL, NULL) != 0) {
        fprintf(stderr, "Error opening input file\n");
        return -1;
    }

    if (avformat_find_stream_info(formatContext, NULL) < 0) {
        fprintf(stderr, "Error finding stream information\n");
        return -1;
    }

    int videoStream = -1;
    for (int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }

    if (videoStream == -1) {
        fprintf(stderr, "No video stream found in the input file\n");
        return -1;
    }

    AVCodecParameters *codecParameters = formatContext->streams[videoStream]->codecpar;
    AVCodec *codec = avcodec_find_decoder(codecParameters->codec_id);
    if (codec == NULL) {
        fprintf(stderr, "Unsupported codec\n");
        return -1;
    }

    AVCodecContext *codecContext = avcodec_alloc_context3(codec);
    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        fprintf(stderr, "Failed to copy codec parameters to codec context\n");
        return -1;
    }

    if (avcodec_open2(codecContext, codec, NULL) < 0) {
        fprintf(stderr, "Failed to open codec\n");
        return -1;
    }

    AVPacket packet;
    av_init_packet(&packet);

    AVFrame *frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Failed to allocate frame\n");
        return -1;
    }

    while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == videoStream) {
            if (avcodec_send_packet(codecContext, &packet) < 0) {
                fprintf(stderr, "Error sending a packet for decoding\n");
                return -1;
            }

            while (avcodec_receive_frame(codecContext, frame) >= 0) {
                // Do something with the video frame, for example, manipulate or replace it

                // ...

                av_frame_unref(frame);
            }
        }

        av_packet_unref(&packet);
    }

    avcodec_free_context(&codecContext);
    av_frame_free(&frame);
    avformat_close_input(&formatContext);

    return 0;
}
