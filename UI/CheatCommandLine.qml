import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: cheatCommandLine_Rec
    Layout.preferredHeight: (cheatImage_Rec.isActivity) ? parent.height / 10 : 0
    Layout.preferredWidth: parent.width
    color:playWindow.thirdaryColor
    border.color: playWindow.borderColor
    radius: 10
    clip: true
    property bool isActivity: false

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 10
        TextField{
            id: cheatCommandLine_Textfield
            Layout.preferredHeight: parent.height / 2
            Layout.fillWidth: true
            placeholderText: "Insert command"
        }
        RowLayout{
            Layout.preferredHeight: parent.height / 2
            Layout.fillWidth: true
            Rectangle{
                Layout.fillWidth: true
            }
            Rectangle{
                id: executeCheatCMD_Rec
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: 50
                color: playWindow.secondaryColor
                border.color: "#05b4ff"
                radius: 5
                property bool isHovered: false

                Rectangle{
                    id: executeCheatCMD_internalRec
                    height: parent.height
                    width: parent.isHovered ? parent.width : 0
                    color: "#83ff05"
                    radius: 5
                    z: 1
                    Behavior on width{
                        NumberAnimation {
                            duration: 100
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                Text {
                    z:2
                    text: "Execute"
                    font.bold: true
                    font.family: "roboto"
                    font.pixelSize: executeCheatCMD_Rec.height / 2
                    color: parent.isHovered ? "black" : "white"
                    anchors.centerIn: parent
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: event.cheatEnable
                    onEntered: {
                        parent.scale = 1.15
                        parent.isHovered = true
                    }
                    onExited: {
                        parent.scale = 1.0
                        parent.isHovered = false
                    }
                    onPressed: {
                        parent.scale = 1.05
                        event.commendEntryPoint(cheatCommandLine_Textfield.text)
                        console.log(cheatCommandLine_Textfield.text)
                    }
                    onReleased: {
                        parent.scale = 1.15
                    }
                }

                Behavior on scale {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }
            Rectangle{
                id: clearCheatCMD_Rec
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: 50
                color: playWindow.secondaryColor
                border.color: "#ff0505"
                radius: 5
                property bool isHovered: false

                Rectangle{
                    id: clearCheatCMD_internalRec
                    height: parent.height
                    width: parent.isHovered ? parent.width : 0
                    color: "#ff6805"
                    radius: 5
                    z: 1
                    Behavior on width{
                        NumberAnimation {
                            duration: 100
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                Text {
                    z:2
                    text: "Clear"
                    font.bold: true
                    font.family: "roboto"
                    font.pixelSize: clearCheatCMD_Rec.height / 2
                    color: parent.isHovered ? "black" : "white"
                    anchors.centerIn: parent
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true
                    onEntered: {
                        parent.scale = 1.15
                        parent.isHovered = true
                    }
                    onExited: {
                        parent.scale = 1.0
                        parent.isHovered = false
                    }
                    onPressed: {
                        parent.scale = 1.05
                        cheatCommandLine_Textfield.text = ""
                    }
                    onReleased: {
                        parent.scale = 1.15
                    }
                }

                Behavior on scale {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }

    Behavior on Layout.preferredHeight {
        NumberAnimation {
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }
}
