import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import "../Resources"

Popup {
    id: shop_popUp
    width: 0
    height: 0
    focus: true
    closePolicy: Popup.NoAutoClose
    anchors.centerIn: parent
    clip: true
    property bool isVisable: false
    padding: 0


    background: Rectangle {
        id: shopPopup_background
        width: shop_popUp.width
        height: shop_popUp.height
        radius: 30
    }

    function openAnimation() {
        shop_popUp_OpenAniamtion.start()
    }

    function closeAnimation() {
        shop_popUp_CloseAniamtion.start()
    }

    Connections {
        target: event
        onOpenShopPopup: {
            shop_popUp.openAnimation();
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#121212"
        Image {
            anchors.fill: parent
            source: "qrc:/images/shop/background.png"
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 20

            GridLayout {
                id: productGrid
                columns: 5
                rowSpacing: 20
                columnSpacing: 20
                Layout.fillWidth: true
                Layout.fillHeight: true

                // 商品卡片範例，其他卡片請類似改寫
                Repeater {
                    model: 5
                    delegate: Item {
                        width: 200
                        height: 330

                        // 模擬陰影
                        Rectangle {
                            anchors.fill: parent
                            radius: 12
                            color: "#2b2b2b"
                            border.color: "#444444"
                            border.width: 1
                        }
                        Rectangle {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            y: parent.height - 10
                            height: 10
                            radius: 12
                            color: "#00000060"
                            opacity: 0.4
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 10

                            Rectangle {
                                width: 180
                                height: 200
                                radius: 8
                                color: "transparent"
                                clip: true
                                Image {
                                    anchors.fill: parent
                                    source: {
                                        switch (index) {
                                            case 3:
                                                return "qrc:/images/shop/index0.png";
                                            case 0:
                                                return "qrc:/images/shop/index1.png";
                                            case 4:
                                                return "qrc:/images/shop/index2.png";
                                            case 1:
                                                return "qrc:/images/shop/index3.png";
                                            case 2:
                                                return "qrc:/images/shop/index4.png";
                                            default:
                                                return "";
                                        }
                                    }
                                    fillMode: Image.PreserveAspectFit
                                }
                            }

                            Text {
                                text: {
                                    switch (index) {
                                        case 3:
                                            return "DISTROY\nIMMOVABLECARD";
                                        case 0:
                                            return "DICE\nCONTROL";
                                        case 4:
                                            return "RANDOM EVENT";
                                        case 1:
                                            return "Road block";
                                        case 2:
                                            return "Rocket";
                                        default:
                                            return "";
                                    }
                                }
                                font.pixelSize: 16
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                color: "#EEEEEE"
                                wrapMode: Text.WordWrap
                            }

                            Item {
                                Layout.fillHeight: true
                            }

                            Button {
                                id: buyButton
                                property bool purchased: false
                                Layout.fillWidth: true
                                enabled: !purchased
                                background: Rectangle {
                                    implicitHeight: 40
                                    radius: 6
                                    color: buyButton.enabled ? "#1E88E5" : "#555555"
                                }
                                contentItem: Text {
                                    text: {
                                        switch (index) {
                                            case 0:
                                                return "price - $1000";
                                            case 1:
                                                return "price - $500";
                                            case 2:
                                                return "price - $10000";
                                            case 3:
                                                return "price - $5000";
                                            case 4:
                                                return "price - $800";
                                            default:
                                                return "";
                                        }
                                    }
                                    anchors.centerIn: parent
                                    color: "white"
                                    font.pixelSize: 14
                                    font.bold: true
                                }
                                onClicked: {
                                    let price = 0;
                                    switch (index) {
                                        case 0:
                                            price = 1000;
                                            break;
                                        case 1:
                                            price = 500;
                                            break;
                                        case 2:
                                            price = 10000;
                                            break;
                                        case 3:
                                            price = 5000;
                                            break;
                                        case 4:
                                            price = 800;
                                            break;
                                    }
                                    if (event.buyItemEntryPoint(price, index)) {
                                        console.log("購買成功")
                                        purchased = true
                                    } else {
                                        console.log("購買失敗")
                                    }
                                }
                            }
                        }
                    }
                }
            }

            RowLayout {
                Layout.preferredWidth: parent.width

                Rectangle {
                    Layout.preferredWidth: 180
                    Layout.preferredHeight: 50
                    Layout.margins: 5
                    radius: 10
                    color: "#2b2b2b"
                    border.color: "#444444"
                    border.width: 1
                    anchors.left: parent.left
                    opacity: 0.9

                    Text {
                        id: moneyText
                        anchors.fill: parent
                        text: "$" + event.displayState.ownMoney
                        font.pixelSize: 18
                        font.bold: true
                        color: "#EEEEEE"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Rectangle {
                    Layout.preferredWidth: 180
                    Layout.preferredHeight: 50
                    Layout.margins: 5
                    radius: 10
                    color: "#2b2b2b"
                    border.color: "#444444"
                    border.width: 1
                    opacity: 0.9
                    anchors.right: parent.right
                    property bool isHovered: false

                    Rectangle {
                        height: parent.height
                        width: parent.isHovered ? parent.width : 0
                        color: "#4e4e4e"
                        opacity: 0.9
                        radius: 5
                        z: 1
                        Behavior on width {
                            NumberAnimation {
                                duration: 100
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }

                    Text {
                        z: 2
                        text: "Close"
                        font.bold: true
                        font.family: "roboto"
                        color: parent.isHovered ? "black" : "white"
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            parent.scale = 1.05
                            parent.isHovered = true
                        }
                        onExited: {
                            parent.scale = 1.0
                            parent.isHovered = false
                        }
                        onPressed: {
                            parent.scale = 1.0
                            shop_popUp.closeAnimation();
                        }
                        onReleased: {
                            parent.scale = 1.05
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

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: shop_popUp.width
                height: shop_popUp.height
                radius: shopPopup_background.radius
            }
        }
    }

    SequentialAnimation {
        id: shop_popUp_CloseAniamtion
        NumberAnimation {
            target: shop_popUp
            property: "height"
            to: 3
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: shop_popUp
            property: "width"
            to: 0
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: shop_popUp
            property: "height"
            to: 0
            duration: 1
            easing.type: Easing.InOutQuad
        }
        ScriptAction {
            script: {
                shop_popUp.close()
            }
        }
    }
    SequentialAnimation {
        id: shop_popUp_OpenAniamtion
        ScriptAction {
            script: {
                shop_popUp.open()
            }
        }
        NumberAnimation {
            target: shop_popUp
            property: "height"
            to: 3
            duration: 1
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: shop_popUp
            property: "width"
            to: 900
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: shop_popUp
            property: "height"
            to: 700
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
}
