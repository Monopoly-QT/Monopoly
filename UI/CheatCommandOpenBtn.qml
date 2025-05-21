import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: cheatImage_Rec
    Layout.preferredWidth: parent.width / 5
    Layout.preferredHeight: parent.height
    color: "transparent"
    radius: 10
    property bool isActivity: false

    Image {
        id: cheatImage
        height: (parent.width < parent.height) ? parent.width * 0.8 : parent.height * 0.8
        width: (parent.width < parent.height) ? parent.width * 0.8 : parent.height * 0.8
        anchors.centerIn: parent
        source: (parent.isActivity) ? "qrc:/images/cheat_1.png" : "qrc:/images/cheat.png"

        Behavior on scale {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

    }

    MouseArea{
        enabled: true
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
            cheatImage.scale = 1.25
        }
        onExited: {
            cheatImage.scale = 1.0
        }
        onPressed: {
            parent.isActivity = !parent.isActivity
            cheatImage.scale = 1.15
        }
        onReleased: {
            cheatImage.scale = 1.25
        }
    }
}
