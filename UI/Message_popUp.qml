import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import "baseWidget"

Popup{
    id: message_popUp
    property string label: "123"
    anchors.centerIn: parent
    width: 0
    height: 0
    focus: true
    closePolicy: Popup.NoAutoClose
    function openAnimation(){
        message_popUp_OpenAniamtion.start()
    }
    function closeAnimation(){
        message_popUp_CloseAniamtion.start()
    }

    background: Rectangle{
        anchors.fill: parent
        radius: 10
        border.color: "#5d7586"
        color: playWindow.secondaryColor
    }

    ColumnLayout{
        anchors.fill: parent
        clip: true
        Rectangle{
            Layout.preferredHeight: parent.height / 1.25
            Layout.preferredWidth: parent.width
            color: "transparent"
            clip: true
            ScrollView{
                width: parent.width
                height: parent.height
                ScrollBar.vertical.policy: ScrollBar.AlwaysOff
                Item {
                    width: Math.max(standardText.implicitWidth, parent.width)
                    height: Math.max(standardText.implicitHeight, parent.height)

                    Standard_Text {
                        id: standardText
                        label: message_popUp.label
                        anchors.centerIn: parent
                    }
                }
                // Standard_Text{
                //     label: message_popUp.label
                //     anchors.centerIn: parent
                // }
            }
        }
        Rectangle{
            Layout.fillHeight: true
        }

        RowLayout{
            Layout.preferredHeight: parent.height / 8
            Layout.preferredWidth: parent.width
            Rectangle{
                Layout.fillWidth: true
            }
            Rectangle {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width / 4
                color: "transparent"
                CostumBtn_Rec {
                    hoverColor: "#ff6805"
                    text: "close"
                    onPressed: {
                        message_popUp_CloseAniamtion.start()
                    }
                }
            }
            Rectangle{
                Layout.preferredWidth: 5
            }
        }
        Rectangle{
            Layout.preferredWidth: 5
        }
    }

    SequentialAnimation{
        id: message_popUp_CloseAniamtion
        NumberAnimation {
            target: message_popUp
            property: "height"
            to : 3
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: message_popUp
            property: "width"
            to : 0
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: message_popUp
            property: "height"
            to : 0
            duration: 1
            easing.type: Easing.InOutQuad
        }
        ScriptAction{
            script: {
                message_popUp.close()
            }
        }
    }
    SequentialAnimation{
        id: message_popUp_OpenAniamtion
        ScriptAction{
            script: {
                message_popUp.open()
            }
        }
        NumberAnimation {
            target: message_popUp
            property: "height"
            to : 3
            duration: 1
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: message_popUp
            property: "width"
            to : 450
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: message_popUp
            property: "height"
            to : 200
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
}
