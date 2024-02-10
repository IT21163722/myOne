<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Video Player</title>
</head>
<body>
    <video id="myVideo" width="640" height="360" controls>
        <!-- Replace 'path/to/your/first/video.mp4' with the actual path to your video file -->
        <source src="path/to/your/first/video.mp4" type="video/mp4">
        Your browser does not support the video tag.
    </video>

    <script>
        const videoPlayer = document.getElementById('myVideo');

        // Array of video sources
        const videoSources = [
            "path/to/your/first/video.mp4",
            "path/to/your/second/video.mp4",
            // Add more video sources as needed
        ];

        let currentVideoIndex = 0;

        // Event listener to detect when the current video ends
        videoPlayer.addEventListener('ended', function() {
            // Increment the current video index
            currentVideoIndex++;

            // If the index exceeds the array length, reset to the first video
            if (currentVideoIndex >= videoSources.length) {
                currentVideoIndex = 0;
            }

            // Change to the next video
            videoPlayer.src = videoSources[currentVideoIndex];
            videoPlayer.load(); // Load the new video
            videoPlayer.play(); // Play the new video
        });
    </script>
</body>
</html>
