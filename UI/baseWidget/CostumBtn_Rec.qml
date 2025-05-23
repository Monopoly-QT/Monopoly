import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property alias text: label.text
    property string textFont: "roboto"
    property bool selected: false
    property bool hovered: false
    property color baseColor: "#505050"
    property color hoverColor: "#808080"
    property color borderColor: "#ff9300"
    property color textColor: "white"
    property real hoverScale: 1.05
    property real pressScale: 1.025
    property real baseScale: 1.0
    signal pressed()

    radius: 5
    color: baseColor
    border.color: borderColor
    scale: baseScale

    anchors.fill:parent

    clip: true

    Text {
        id: label
        anchors.centerIn: parent
        font.family: textFont
        font.pixelSize: 10
        font.bold: true
        color: textColor
        z: 1
    }

    Rectangle {
        width: hovered ? parent.width : 0
        height: parent.height
        radius: parent.radius
        color: hoverColor
        z: 0

        Behavior on width {
            NumberAnimation {
                duration: 100
                easing.type: Easing.InOutQuad
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.hovered = true
            root.scale = hoverScale
        }
        onExited: {
            root.hovered = false
            root.scale = baseScale
        }
        onPressed: {
            root.pressed()
            root.scale = pressScale
        }
        onReleased: {
            root.scale = hoverScale
        }
    }

    Behavior on scale {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
}
