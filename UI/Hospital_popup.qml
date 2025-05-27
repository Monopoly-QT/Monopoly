import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import "baseWidget"

Popup {
    id: root
    width: 0
    height: 0
    closePolicy: Popup.NoAutoClose
    focus: true
    anchors.centerIn: parent
    property string text: "empty"

    function openAnimation() {
        text = "Remaining Days:"+event.getHosiptalRemainingDays()+"\nYou can be discharged early for $"+event.getHosiptalRemainingDays() * 1000+".\nOr skip and roll dice to discharged early (>8).";
        root_OpenAniamtion.start()
    }

    function closeAnimation() {
        root_CloseAniamtion.start()
    }


    background: Rectangle {
        anchors.fill: parent
        radius: 10
        border.color: "#5d7586"
        color: playWindow.secondaryColor
    }

    ColumnLayout {
        anchors.fill: parent
        clip: true
        Rectangle {
            Layout.preferredHeight: parent.height / 4
            Layout.preferredWidth: parent.width
            color: "transparent"
            clip: true
            Standard_Text {
                label: "Hospital"
            }
        }

        Rectangle {
            Layout.preferredHeight: parent.height / 4
            Layout.preferredWidth: parent.width
            color: "transparent"
            clip: true
            Standard_Text {
                label: root.text
            }
        }

        Rectangle {
            Layout.fillHeight: true
            color: "transparent"
        }

        RowLayout {
            Layout.preferredHeight: parent.height / 4
            Layout.preferredWidth: parent.width
            clip: true
            Rectangle {
                Layout.fillWidth: true
            }
            Rectangle {
                Layout.preferredHeight: parent.height / 2
                Layout.preferredWidth: parent.width / 3
                color: "transparent"
                CostumBtn_Rec {
                    hoverColor: "#83ff05"
                    text: "Discharged Early"
                    textColor: (hovered) ? "blcak" : "white"
                    onPressed: {
                        console.log("Discharged early")
                        event.leaveEarly();
                        root_CloseAniamtion.start()
                    }
                }
            }
            Rectangle {
                Layout.preferredHeight: parent.height / 2
                Layout.preferredWidth: parent.width / 3
                color: "transparent"
                CostumBtn_Rec {
                    hoverColor: "#ff6805"
                    text: "Skip and roll dice"
                    textColor: (hovered) ? "blcak" : "white"
                    onPressed: {
                        root_CloseAniamtion.start()
                    }
                }
            }
            Rectangle {
                Layout.preferredWidth: 5
            }
        }
    }

    SequentialAnimation {
        id: root_CloseAniamtion
        NumberAnimation {
            target: root
            property: "height"
            to: 3
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: root
            property: "width"
            to: 0
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: root
            property: "height"
            to: 0
            duration: 1
            easing.type: Easing.InOutQuad
        }
        ScriptAction {
            script: {
                root.close()
            }
        }
    }
    SequentialAnimation {
        id: root_OpenAniamtion
        ScriptAction {
            script: {
                root.open()
            }
        }
        NumberAnimation {
            target: root
            property: "height"
            to: 3
            duration: 1
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: root
            property: "width"
            to: 400
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: root
            property: "height"
            to: 300
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
}
