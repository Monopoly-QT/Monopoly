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
    signal updateComboBox();

    function openAnimation() {
        root_OpenAniamtion.start()
        root.updateComboBox();
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
                label: root.text
            }
        }

        Rectangle {
            Layout.preferredHeight: parent.height / 4
            Layout.preferredWidth: parent.width
            color: "transparent"
            clip: true
            Standard_Text {
                label: "Sorry, you're bankrupt.\nYou need to sell land to make money."
            }
        }

        ComboBox {
            id: removeCoordinate
            Layout.fillWidth: true
            model: event.useCard.displayOwnLand
            onCurrentIndexChanged: {
                console.log("Selected:", currentText)
            }
            function onUpdateComboBox() {
                removeCoordinate.model = event.getOwnLand();
            }
            Component.onCompleted: {
                root.updateComboBox.connect(onUpdateComboBox);
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
                Layout.preferredWidth: parent.width / 4
                color: "transparent"
                CostumBtn_Rec {
                    hoverColor: "#83ff05"
                    text: "Sell"
                    textColor: (hovered) ? "blcak" : "white"
                    enabled: removeCoordinate.model.length > 0
                    onPressed: {
                        console.log("Sell")
                        event.sellLandFromStrUseWhenDieEntryPoint(removeCoordinate.currentText)
                        root_CloseAniamtion.start()
                    }
                }
            }
            Rectangle {
                Layout.preferredHeight: parent.height / 2
                Layout.preferredWidth: parent.width / 4
                color: "transparent"
                CostumBtn_Rec {
                    hoverColor: "#83ff05"
                    text: "Suicidal"
                    textColor: (hovered) ? "blcak" : "white"
                    onPressed: {
                        console.log("Suicidal")
                        event.suicidal()
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
            to: 300
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: root
            property: "height"
            to: 200
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
}
