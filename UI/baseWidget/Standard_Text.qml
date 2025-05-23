import QtQuick 2.15

Text {
    id: root
    property alias label: root.text
    property string family: "roboto"
    property bool isBold: true
    property color fontColor: "white"
    property int fontSize: 15
    font.bold: isBold
    font.family: family
    font.pixelSize: fontSize
    color: fontColor
    anchors.centerIn: parent
}
