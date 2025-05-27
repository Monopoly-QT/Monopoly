import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects
import Qt5Compat.GraphicalEffects

import "."
import "../Resources"

Window {
    width: 1280
    height: 720
    visible: true

    StackView{
        id: stack
        anchors.fill: parent
        pushEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 0
                }
            }

        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 0
            }
        }

        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 0
            }
        }

        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 0
            }
        }
        initialItem: playWindow_component
    }

    Component{
        id:playWindow_component
        Item{
            Rectangle {
                id: playWindow
                color: playWindow.backGroundColor
                anchors.fill: parent
                property color backGroundColor: "#3c3c3c"
                property color secondaryColor: "#454545"
                property color thirdaryColor: "#505050"
                property color borderColor: "#ff9300"
                property color hoverColor: "#808080"
                property color pressColor: "#747474"
                property int dicePoint: 0
                Rectangle {
                    id: movePoint
                    height: 10
                    width: 10
                    color: event.movePoint.displayColor
                    x: map_Grid.coordinateList[0].posX
                    y: map_Grid.coordinateList[0].posY
                    z: 2
                    radius: width / 2
                    visible: event.movePoint.isvisable
                    property int moveDuaration: 0

                    Behavior on x {
                        NumberAnimation {
                            duration: movePoint.moveDuaration
                            easing.type: Easing.InOutQuad
                        }
                    }

                    Behavior on y {
                        NumberAnimation {
                            duration: movePoint.moveDuaration
                            easing.type: Easing.InOutQuad
                        }
                    }

                    SequentialAnimation {
                        id: movePoint_scaleAnimation
                        NumberAnimation {
                            target: movePoint
                            property: "scale"
                            to: 2.0
                            duration: movePoint.moveDuaration / 2
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: movePoint
                            property: "scale"
                            to: 1.0
                            duration: movePoint.moveDuaration / 2
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "transparent"
                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 10
                            color: "transparent"
                            GridLayout {
                                id: map_Grid
                                property var coordinateList: []
                                anchors.fill: parent
                                columns: 11
                                columnSpacing: 0
                                rowSpacing: 0
                                property int order: 1
                                Repeater {
                                    id: mapGenerate
                                    model: event.mapList
                                    Rectangle {
                                        Layout.preferredHeight: parent.height / 11
                                        Layout.preferredWidth: parent.width / 11
                                        color: playWindow.secondaryColor
                                        border.color: playWindow.borderColor
                                        border.width: 1
                                        opacity: model.isDisplay ? 1 : 0

                                        ColumnLayout {
                                            anchors.fill: parent
                                            spacing: 0
                                            //order and name
                                            Rectangle {
                                                Layout.preferredHeight: parent.height / 3
                                                Layout.preferredWidth: parent.width
                                                Layout.alignment: Qt.AlignTop
                                                color: model.displayColor
                                                border.color: playWindow.borderColor
                                                RowLayout {
                                                    anchors.fill: parent
                                                    anchors.margins: 5
                                                    spacing: 0
                                                    //land order
                                                    Text {
                                                        text: model.order + "."
                                                        color: "white"
                                                        font.bold: true
                                                        font.family: "roboto"
                                                        font.pixelSize: (parent.height / 1.2 < parent.height / 1.2) ? parent.height / 1.2 : parent.height / 1.2
                                                    }

                                                    //land name
                                                    Rectangle {
                                                        Layout.fillHeight: true
                                                        Layout.fillWidth: true
                                                        color: "transparent"
                                                        Text {
                                                            anchors.centerIn: parent
                                                            text: model.showTranslation ? model.translation : model.name
                                                            color: "white"
                                                            font.bold: true
                                                            font.family: "roboto"
                                                            font.pixelSize: (parent.height / 1.2 < parent.height / 2) ? parent.height / 1.2 : parent.height / 1.2
                                                        }

                                                        MouseArea {
                                                            anchors.fill: parent
                                                            hoverEnabled: true
                                                            onEntered: {
                                                                model.showTranslation = true;
                                                            }

                                                            onExited: {
                                                                model.showTranslation = false;
                                                            }
                                                        }
                                                    }

                                                }
                                            }

                                            Rectangle {

                                                Layout.preferredHeight: parent.height / 3 * 2
                                                Layout.preferredWidth: parent.width
                                                color: "transparent"

                                                property real centerX: x + width / 2
                                                property real centerY: y + height / 2
                                                property var pt

                                                Image {
                                                    id: roadBlock
                                                    source: "qrc:/images/roadBlock.png"
                                                    height: parent.height
                                                    width: height
                                                    anchors.centerIn: parent
                                                    z:1
                                                    opacity: 0.25
                                                    visible: model.isRoadBlock
                                                }

                                                RowLayout {
                                                    anchors.fill: parent
                                                    anchors.margins: 5
                                                    //player stay
                                                    ColumnLayout {
                                                        Layout.preferredHeight: parent.height
                                                        Layout.preferredWidth: parent.width / 3
                                                        spacing: 0

                                                        //player1
                                                        Rectangle {
                                                            Layout.fillHeight: true
                                                            Layout.fillWidth: true
                                                            color: "transparent"
                                                            Rectangle {
                                                                anchors.centerIn: parent
                                                                height: parent.height / 2
                                                                width: height
                                                                radius: width / 2
                                                                color: "#ff1700"
                                                                visible: model.playerStay[0] === 1 ? true : false
                                                            }
                                                        }
                                                        //player2
                                                        Rectangle {
                                                            Layout.fillHeight: true
                                                            Layout.fillWidth: true
                                                            color: "transparent"
                                                            Rectangle {
                                                                anchors.centerIn: parent
                                                                height: parent.height / 2
                                                                width: height
                                                                radius: width / 2
                                                                color: "#009aff"
                                                                visible: model.playerStay[1] === 1 ? true : false
                                                            }
                                                        }
                                                        //player3
                                                        Rectangle {
                                                            Layout.fillHeight: true
                                                            Layout.fillWidth: true
                                                            color: "transparent"
                                                            Rectangle {
                                                                anchors.centerIn: parent
                                                                height: parent.height / 2
                                                                width: height
                                                                radius: width / 2
                                                                color: "#0fff00"
                                                                visible: model.playerStay[2] === 1 ? true : false
                                                            }
                                                        }
                                                        //player4
                                                        Rectangle {
                                                            Layout.fillHeight: true
                                                            Layout.fillWidth: true
                                                            color: "transparent"
                                                            Rectangle {
                                                                anchors.centerIn: parent
                                                                height: parent.height / 2
                                                                width: height
                                                                radius: width / 2
                                                                color: "#ffcb00"
                                                                visible: model.playerStay[3] === 1 ? true : false
                                                            }
                                                        }
                                                    }
                                                    //player stay end

                                                    ColumnLayout {
                                                        Layout.preferredHeight: parent.height
                                                        Layout.preferredWidth: parent.width * 2 / 3
                                                        spacing: 0

                                                        RowLayout {
                                                            Layout.fillHeight: true
                                                            Layout.fillWidth: true
                                                            visible: (model.isDisplayBuilding[0] === 1 || model.isDisplayBuilding[1] === 1) ? true : false
                                                            spacing: 1
                                                            //house1
                                                            Rectangle {
                                                                Layout.fillHeight: true
                                                                Layout.fillWidth: true
                                                                color: "transparent"
                                                                visible: model.isDisplayBuilding[0] === 1 ? true : false
                                                                Image {
                                                                    anchors.centerIn: parent
                                                                    height: (parent.height > parent.width) ? parent.width : parent.height
                                                                    width: (parent.height > parent.width) ? parent.width : parent.height
                                                                    source: "qrc:/images/house.png"
                                                                }
                                                            }
                                                            //house1 end
                                                            //house2
                                                            Rectangle {
                                                                Layout.fillHeight: true
                                                                Layout.fillWidth: true
                                                                color: "transparent"
                                                                visible: model.isDisplayBuilding[1] === 1 ? true : false
                                                                Image {
                                                                    anchors.centerIn: parent
                                                                    height: (parent.height > parent.width) ? parent.width : parent.height
                                                                    width: (parent.height > parent.width) ? parent.width : parent.height
                                                                    source: "qrc:/images/house.png"
                                                                }
                                                            }
                                                            //house2 end
                                                        }

                                                        RowLayout {
                                                            Layout.fillHeight: true
                                                            Layout.fillWidth: true
                                                            spacing: 1
                                                            visible: (model.isDisplayBuilding[2] === 1 || model.isDisplayBuilding[3] === 1) ? true : false
                                                            //house3
                                                            Rectangle {
                                                                Layout.fillHeight: true
                                                                Layout.fillWidth: true
                                                                color: "transparent"
                                                                visible: model.isDisplayBuilding[2] === 1 ? true : false
                                                                Image {
                                                                    anchors.centerIn: parent
                                                                    height: (parent.height > parent.width) ? parent.width : parent.height
                                                                    width: (parent.height > parent.width) ? parent.width : parent.height
                                                                    source: "qrc:/images/house.png"
                                                                }
                                                            }
                                                            //house3 end
                                                            //building
                                                            Rectangle {
                                                                Layout.fillHeight: true
                                                                Layout.fillWidth: true
                                                                color: "transparent"
                                                                visible: model.isDisplayBuilding[3] === 1 ? true : false
                                                                Image {
                                                                    anchors.centerIn: parent
                                                                    height: (parent.height > parent.width) ? parent.width : parent.height
                                                                    width: (parent.height > parent.width) ? parent.width : parent.height
                                                                    source: "qrc:/images/building.png"
                                                                }
                                                            }
                                                            //building end
                                                        }
                                                    }
                                                }
                                                Timer {
                                                    id: buffer
                                                    interval: 50
                                                    running: true
                                                    repeat: true
                                                    onTriggered: {
                                                        if (parent.width > 0 && parent.height > 0) {
                                                            if (model.isDisplay === true) {
                                                                parent.pt = mapToItem(null, parent.centerX, parent.centerY);
                                                                console.log("Correct global position:", parent.pt.x, parent.pt.y);
                                                                // map_Grid.coordinateList.push({posX:parent.pt.x,posY:parent.pt.y})
                                                                event.addMapPosXandPosY(parent.pt.x, parent.pt.y)
                                                            } else {
                                                                event.addMapPosXandPosY(0, 0)
                                                            }

                                                            stop();
                                                        }
                                                    }
                                                }
                                                onHeightChanged: {
                                                    map_Grid.coordinateList = []
                                                    event.clearMapPosXandPosY()
                                                    buffer.start()
                                                }
                                                onWidthChanged: {
                                                    map_Grid.coordinateList = []
                                                    event.clearMapPosXandPosY()
                                                    buffer.start()
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: parent.width / 5
                        color: playWindow.secondaryColor
                        ColumnLayout {
                            id: stateColumn
                            anchors.fill: parent
                            anchors.margins: 10

                            StateContainer {
                                id: stateContainer
                            }

                            RowLayout {
                                Layout.preferredHeight: parent.height / 20
                                Layout.preferredWidth: parent.width

                                Rectangle {
                                    Layout.fillWidth: true
                                }

                                CardOpenBtn {
                                    id: useCard_Rec
                                }

                                CheatCommandOpenBtn {
                                    id: cheatImage_Rec
                                }
                            }

                            Rectangle {
                                Layout.fillHeight: true
                            }

                            CheatCommandLine {
                                id: cheatCommandLine_Rec
                            }

                            Dice {
                                id: diceContainer
                            }
                        }
                    }
                }
                Connections {
                    target: event
                    onMovePointStartMove: {
                        movePoint.moveDuaration = 150
                        movePoint.x = event.movePoint.changeX - (movePoint.width / 2)
                        movePoint.y = event.movePoint.changeY - (movePoint.height / 2)
                        movePoint_scaleAnimation.start()
                    }
                    onMovePointInitialize: {
                        movePoint.moveDuaration = 0
                        movePoint.x = event.movePoint.changeX - (movePoint.width / 2)
                        movePoint.y = event.movePoint.changeY - (movePoint.height / 2)
                    }
                    onOpenMessage: {
                        if(!message.visible)
                            message.openAnimation()
                    }
                    onOpenBuyPopup: {
                        if(buyLand.visible)
                            buyLand.closeAnimation()
                        else
                            buyLand.openAnimation()
                    }
                    onOpenUpgradePopup: (upgradeable,sellable) => {
                        upgradeOrSell.isUpgradeable = upgradeable
                        upgradeOrSell.isSellable = sellable
                        if(upgradeOrSell.visible)
                            upgradeOrSell.closeAnimation()
                        else
                            upgradeOrSell.openAnimation()
                    }
                    onOpenEndPopup: {
                        if(endgame.visible)
                            endgame.closeAnimation()
                        else
                            endgame.openAnimation()
                    }
                    onOpenBankruptcy: {
                        if(bankruptcy.visible)
                            bankruptcy.closeAnimation()
                        else
                            bankruptcy.openAnimation()
                    }
                    onOpenDragonGate: {
                        stack.push("DragonGate.qml")
                    }
                    onOpenHorseRacing: {
                        stack.push("HorseRacing.qml")
                    }

                    onOpenHospitalPopups: {
                        if(hospital.visible)
                            hospital.closeAnimation()
                        else
                            hospital.openAnimation()
                    }

                    onCloseAllPopups: {
                        if (card_popUp.visible) {
                            card_popUp.closeAnimation();
                        }
                        if (shop_popUp.visible) {
                            shop_popUp.closeAnimation();
                        }
                        if (message.visible) {
                            message.closeAnimation();
                        }
                        if (buyLand.visible) {
                            buyLand.closeAnimation();
                        }
                        if (upgradeOrSell.visible) {
                            upgradeOrSell.closeAnimation();
                        }
                        if (bankruptcy.visible) {
                            bankruptcy.closeAnimation();
                        }
                        if (hospital.visible) {
                            hospital.closeAnimation();
                        }
                    }
                }
            }

            CardPopup {
                id: card_popUp
            }

            ShopPopup {
                id: shop_popUp
            }

            Message_popUp{
                id:message
                label: event.displayMessage_messagePopup
                z:4
            }

            BuyLand_popUp{
                id:buyLand
                text: event.displayMessage_buyPopup
                z:3
            }

            UpgradeOrSell_popUp{
                id:upgradeOrSell
                text: event.displayMessage_upgradePopup
                z:2
            }

            Bankruptcy_popUp{
                id:bankruptcy
                text: event.displayMessage_bankruptcypopUp
                z:1
            }

            EndPopUp{
                id:endgame
                text: event.displayMessage_endPopup
            }

            Hospital_popup{
                id:hospital
                text: event.displayMessage_endPopup
            }

            FastBlur {
                id: theBlur;
                visible: card_popUp.visible || shop_popUp.visible || message.visible || buyLand.visible || upgradeOrSell.visible || bankruptcy.visible || endgame.visible || hospital.visible
                anchors.fill: parent
                source: playWindow
                radius: 32
                cached: false
                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                }
            }

            Rectangle{
                visible: card_popUp.visible || shop_popUp.visible || message.visible || buyLand.visible || upgradeOrSell.visible || bankruptcy.visible || endgame.visible || hospital.visible
                anchors.fill: parent
                color: "black"
                opacity: 0.2
            }

            // 宣告 RefreshPopup
            RefreshPopup {
                id: refreshPopup
            }

            function showRefresh() {
                refreshPopup.startRefresh()
            }
        }
    }
}
