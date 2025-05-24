import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects


Rectangle {
    id: diceContainer
    Layout.preferredHeight: parent.height / 10
    Layout.preferredWidth: parent.width
    color: playWindow.thirdaryColor
    border.color: playWindow.borderColor
    radius: 10
    enabled: event.diceEnabled
    property bool isHovered: false
    property bool isPressed: false


    MouseArea {
        id: diceBtn
        anchors.fill: parent
        hoverEnabled: diceContainer.enabled

        onEntered: {
            parent.scale = 1.015
            diceContainer.isHovered = true
        }
        onExited: {
            parent.scale = 1.0
            diceContainer.isHovered = false
        }
        onPressed: {
            parent.scale = 1.0
            diceContainer.isPressed = true
            if (diceTimer.running === false) {
                diceTimer.start()
                event.diceEnabled = false;
            }
        }
        onReleased: {
            parent.scale = 1.015
            diceContainer.isPressed = false
        }
    }
    Timer {
        id: diceTimer
        interval: 50
        repeat: true
        running: false

        property int time: 1000

        onTriggered: {
            time = time - 50
            diceA.rollDice(114514)
            diceB.rollDice(0)
            if (time <= 0) {
                diceTimer.stop();
                time = 1000;
                playWindow.dicePoint = diceA.dicePoint + diceB.dicePoint + 2
                event.moveEntryPoint(playWindow.dicePoint)
            }
        }
    }
    Behavior on scale {
        NumberAnimation {
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }

    Rectangle {
        height: parent.height
        width: diceContainer.isHovered ? parent.width : 0
        radius: parent.radius
        color: diceContainer.isPressed ? playWindow.pressColor : playWindow.hoverColor
        z: 1
        Behavior on width {
            NumberAnimation {
                duration: 100
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        z: 2
        Rectangle {
            Layout.fillWidth: true
        }
        //diceA
        Rectangle {
            id: rec_diceA
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: height
            color: "white"
            radius: 5
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 5
                RowLayout {
                    Layout.preferredHeight: parent.height / 3
                    Layout.preferredWidth: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Rectangle {//dicePointA
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceAShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointB
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceBShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointC
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceCShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }
                }
                RowLayout {
                    Layout.preferredHeight: parent.height / 3
                    Layout.preferredWidth: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Rectangle {//dicePointD
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceDShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }

                }
                RowLayout {
                    Layout.preferredHeight: parent.height / 3
                    Layout.preferredWidth: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Rectangle {//dicePointE
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceEShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointF
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceFShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointG
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceA.DiceGShow ? diceA.pointColor : "white"
                        radius: width / 2
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }
                }
            }
        }
        //diceB
        Rectangle {
            id: rec_diceB
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: height
            color: "white"
            radius: 5
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 5
                RowLayout {
                    Layout.preferredHeight: parent.height / 3
                    Layout.preferredWidth: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Rectangle {//dicePointA
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceAShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointB
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceBShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointC
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceCShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }

                }
                RowLayout {
                    Layout.preferredHeight: parent.height / 3
                    Layout.preferredWidth: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Rectangle {//dicePointD
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceDShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }

                }
                RowLayout {
                    Layout.preferredHeight: parent.height / 3
                    Layout.preferredWidth: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Rectangle {//dicePointE
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceEShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointF
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceFShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }
                    Rectangle {//dicePointG
                        Layout.preferredHeight: width
                        Layout.preferredWidth: parent.width / 5
                        color: diceB.DiceGShow ? diceB.pointColor : "white"
                        radius: width / 2
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }
                }
            }
        }
        Rectangle {
            Layout.fillWidth: true
        }
    }
    Rectangle {
        anchors.fill: parent
        color: "#3a3a3a"
        opacity: 0.5
        z: parent.children.length
        visible: !diceContainer.enabled
        radius: parent.radius
    }

}
