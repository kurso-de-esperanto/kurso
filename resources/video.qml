import QtQuick 2.9
import QtMultimedia 5.12

Item {

    Video {
        id: video
        width : 320
        height : 240
        source: "assets:/video/lec02/jen_video.mp4"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()

            }
        }

        focus: true

    }
}

