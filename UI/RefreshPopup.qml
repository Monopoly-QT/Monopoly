// RefreshPopup.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: refreshPopup
    modal: true
    focus: true
    width: parent.width
    height: parent.height
    background: Rectangle { color: "black" }

    property bool isRunning: false

       function start() {
           // Reset state
           loadingGroup.visible = true
           successText.visible = false
           stage1Timer.restart()
           isRunning = true
           open()
       }

    // 動畫區塊（圓圈＋Refreshing字樣）
    Item {
        id: loadingGroup
        anchors.centerIn: parent
        visible: true

        Rectangle {
            width: 150
            height: 150
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter

            Canvas {
                id: spinner
                anchors.fill: parent
                renderTarget: Canvas.Image
                contextType: "2d"
                Component.onCompleted: requestPaint()

                property real rotation: 0

                onPaint: {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)

                    ctx.save()
                    ctx.translate(width / 2, height / 2)
                    ctx.rotate(Math.PI * rotation / 180)

                    for (var i = 0; i < 12; i++) {
                        ctx.beginPath()
                        ctx.globalAlpha = i / 12
                        ctx.fillStyle = "#555"
                        ctx.arc(0, -60, 8, 0, 2 * Math.PI)
                        ctx.fill()
                        ctx.rotate(Math.PI / 6)
                    }

                    ctx.restore()
                }

                Timer {
                    interval: 50
                    running: true
                    repeat: true
                    onTriggered: {
                        spinner.rotation += 30
                        spinner.requestPaint()
                    }
                }
            }
        }

        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -80
            text: "Refreshing..."
            font.family: "Time News Roman"
            font.pixelSize: 30
            color: "white"
        }
    }

    Text {
        id: successText
        text: "Refresh Successfully"
        font.family: "Time News Roman"
        anchors.centerIn: parent
        visible: false
        font.pixelSize: 30
        color: "lightgreen"
    }

    Timer {
        id: stage1Timer
        interval: 3000
        running: true
        repeat: false
        onTriggered: {
            loadingGroup.visible = false
            successText.visible = true
            stage2Timer.start()
        }
    }

    Timer {
        id: stage2Timer
        interval: 1000
        running: false
        repeat: false
        onTriggered: {
            refreshPopup.close()
        }
    }

    onOpened: stage1Timer.start()
}
