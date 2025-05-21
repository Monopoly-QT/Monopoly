import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: stateContainer
    Layout.preferredHeight: parent.height / 6
    Layout.preferredWidth: parent.width
    color:playWindow.thirdaryColor
    border.color: playWindow.borderColor
    border.width: 2
    radius: 10
    layer.enabled: true

    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: playerNum_Rec
            Layout.preferredHeight: stateContainer.height * 2 / 3
            Layout.preferredWidth:  stateContainer.width
            Layout.alignment: Qt.AlignTop
            border.color: playWindow.borderColor
            color: "transparent"
            topLeftRadius: 10
            topRightRadius: 10
            clip: true
            RowLayout{
                anchors.fill: parent
                anchors.margins: 5
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    Image {
                        anchors.centerIn: parent
                        height: parent.height
                        width: height * 0.66
                        source: event.displayState.imageSource
                    }
                }
                Text {
                    id: playerNum
                    text: event.displayState.name
                    font.bold: true
                    font.pixelSize: parent.width / 15
                    font.family: "roboto"
                    color: "white"
                }
            }
        }
        RowLayout{
            id: moneyContainer_Rowlayout
            Layout.preferredHeight: stateContainer.height / 3
            Layout.preferredWidth:  stateContainer.width
            Rectangle{
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "transparent"
                Image {
                    id:moneyImage
                    anchors.centerIn: parent
                    height: (parent.width < parent.height) ? parent.width  : parent.height
                    width: height
                    source: "qrc:/images/money.png"
                }
            }
            Rectangle{
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "transparent"
                Text{
                    anchors.centerIn: parent
                    id: playerOwnMoney
                    text: event.displayState.ownMoney
                    font.bold: true
                    font.pixelSize: 15
                    font.family: "roboto"
                    color: "white"
                }
            }
        }
    }
}
