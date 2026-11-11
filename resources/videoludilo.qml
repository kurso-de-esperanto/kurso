import QtQuick 2.12
import QtMultimedia 5.12

Rectangle {
    id: rect
    width: 320
    height: 240
    color: "black"

    Image {
        anchors.centerIn: parent
        //anchors.bottom: parent.bottom
        //anchors.right: parent.right
        source: "qrc:/ikonoj_androjdo/jen_video_startu.png"
    }

    MediaPlayer {
        id: player
        source: "assets:/video/lec02/jen_video.mp4"
    }

    VideoOutput {
        id: videoOutput
        source: player
        anchors.centerIn: parent
        //anchors.bottom: parent.bottom
        //anchors.right: parent.right
    }

    MouseArea {
        anchors.fill: rect
        onClicked: {
          player.playbackState == MediaPlayer.PlayingState ? player.pause() : player.play()

        }
    }
}
