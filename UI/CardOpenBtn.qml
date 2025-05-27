import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: useCard_Rec
    Layout.preferredWidth: parent.width / 5
    Layout.preferredHeight: parent.height
    color: "transparent"
    radius: 10
    property bool isHovered: false

    Image {
        id: cardImage
        height: (parent.width < parent.height) ? parent.width * 0.8 : parent.height * 0.8
        width: (parent.width < parent.height) ? parent.width * 0.8 : parent.height * 0.8
        anchors.centerIn: parent
        source: "qrc:/images/card.png"

        Behavior on scale {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
    }

    MouseArea{
        enabled: event.cardEnabled
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
            cardImage.scale = 1.25
        }
        onExited: {
            cardImage.scale = 1.0
        }
        onPressed: {
            cardImage.scale = 1.15
            if(card_popUp.visible === false){
                card_popUp.openAnimation()
            }
            else{
                card_popUp.closeAnimation()
            }
        }
        onReleased: {
            cardImage.scale = 1.25
        }
    }
}
