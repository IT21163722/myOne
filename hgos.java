import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.stage.Stage;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class VideoPlayer extends Application {

    private List<String> videoPaths = new ArrayList<>();
    private int currentVideoIndex = 0;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // Add video paths to the list
        videoPaths.add("path/to/your/first/video.mp4");
        videoPaths.add("path/to/your/second/video.mp4");
        // Add more video paths as needed

        // Create the media player
        MediaPlayer mediaPlayer = createMediaPlayer();

        // Create the media view
        MediaView mediaView = new MediaView(mediaPlayer);

        // Create the scene
        Scene scene = new Scene(mediaView, 640, 360);

        // Set up the stage
        primaryStage.setTitle("Video Player");
        primaryStage.setScene(scene);
        primaryStage.show();

        // Play the first video
        playNextVideo();
    }

    private MediaPlayer createMediaPlayer() {
        Media media = new Media(new File(videoPaths.get(currentVideoIndex)).toURI().toString());
        MediaPlayer mediaPlayer = new MediaPlayer(media);

        // Set up event listener for when the current video ends
        mediaPlayer.setOnEndOfMedia(this::playNextVideo);

        return mediaPlayer;
    }

    private void playNextVideo() {
        currentVideoIndex++;

        if (currentVideoIndex >= videoPaths.size()) {
            currentVideoIndex = 0;
        }

        MediaPlayer mediaPlayer = createMediaPlayer();
        mediaPlayer.play();
    }
}
