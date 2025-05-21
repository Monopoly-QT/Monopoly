import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup{
    id: card_popUp
    width: 0
    height: 0
    focus: true
    closePolicy: Popup.NoAutoClose
    anchors.centerIn: parent
    clip: true
    property bool isVisable: false
    property color popUp_BtnColor: "#6f6b6b"

    function openAnimation(){
        card_popUp_OpenAniamtion.start()
    }

    function closeAnimation(){
        card_popUp_CloseAniamtion.start()
    }

    background: Rectangle{
        anchors.fill: parent
        radius: 10
        border.color: "#5d7586"
        color: playWindow.secondaryColor
    }

    ScrollView {
        anchors.fill: parent
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        ColumnLayout {
            anchors.fill: parent
            spacing: 5
            anchors.margins: 10

            //rocketCard
            Rectangle {
                id: rocketCard
                Layout.fillWidth: true
                Layout.preferredHeight: isOpen ? 250 + 40 : 40
                radius: 10
                color: playWindow.thirdaryColor
                border.color: playWindow.borderColor
                property bool isOpen: false
                property int selectIndex: -1
                clip: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 3
                    clip: true
                    RowLayout {
                        Layout.fillWidth: true
                        Rectangle {
                            Layout.fillWidth: true
                            color: "transparent"
                        }

                        Rectangle {
                            width: 30
                            height: 30
                            color: card_popUp.popUp_BtnColor
                            radius: 10
                            Text {
                                anchors.centerIn: parent
                                text: "◀"
                                color: "white"
                                transformOrigin: Item.Center
                                rotation: rocketCard.isOpen ? -90 : 0
                                Behavior on rotation {
                                    NumberAnimation {
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    rocketCard.isOpen = !rocketCard.isOpen
                                }
                            }
                        }
                    }
                    Rectangle{
                        Layout.preferredHeight: 250
                        Layout.fillWidth: true
                        color: "transparent"
                        ColumnLayout{
                            anchors.fill: parent
                            anchors.margins: 5
                            Text {
                                text: "Target"
                                font.family: "roboto"
                                font.pixelSize: 12
                                color: "white"
                                font.bold: true
                                Layout.alignment: Qt.AlignLeft
                            }
                            RowLayout{
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: 20
                                spacing: 5
                                //player1
                                Rectangle{
                                    Layout.preferredHeight: parent.height
                                    Layout.fillWidth: true
                                    color: (rocketCard.selectIndex == 0) ? "#83ff05" : card_popUp.popUp_BtnColor
                                    border.color: "#5d7586"
                                    radius: 5
                                    property bool isHovered: false

                                    Text {
                                        text: "player1"
                                        font.family: "roboto"
                                        font.pixelSize: 10
                                        font.bold: true
                                        color: "black"
                                        anchors.centerIn:parent
                                        z: 1
                                    }

                                    Rectangle{
                                        width: parent.isHovered ? parent.width : 0
                                        height: parent.height
                                        color:(rocketCard.selectIndex == 0)? "transparent" : "#83ff05"
                                        radius: 5
                                        Behavior on width{
                                            NumberAnimation {
                                                duration: 100
                                                easing.type: Easing.InOutQuad
                                            }
                                        }
                                    }

                                    MouseArea{
                                        z: 2
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.isHovered = true
                                            parent.scale = 1.05
                                        }

                                        onExited: {
                                            parent.isHovered = false
                                            parent.scale = 1.0
                                        }

                                        onPressed: {
                                            rocketCard.selectIndex = 0
                                            parent.scale = 1.025
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
                                //player1 end
                                //player2
                                Rectangle{
                                    Layout.preferredHeight: parent.height
                                    Layout.fillWidth: true
                                    color: (rocketCard.selectIndex == 1) ? "#83ff05" : card_popUp.popUp_BtnColor
                                    border.color: "#5d7586"
                                    radius: 5
                                    property bool isHovered: false

                                    Text {
                                        text: "player2"
                                        font.family: "roboto"
                                        font.pixelSize: 10
                                        font.bold: true
                                        color: "black"
                                        anchors.centerIn:parent
                                        z: 1
                                    }

                                    Rectangle{
                                        width: parent.isHovered ? parent.width : 0
                                        height: parent.height
                                        color:(rocketCard.selectIndex == 1)? "transparent" : "#83ff05"
                                        radius: 5
                                        Behavior on width{
                                            NumberAnimation {
                                                duration: 100
                                                easing.type: Easing.InOutQuad
                                            }
                                        }
                                    }

                                    MouseArea{
                                        z: 2
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.isHovered = true
                                            parent.scale = 1.05
                                        }

                                        onExited: {
                                            parent.isHovered = false
                                            parent.scale = 1.0
                                        }

                                        onPressed: {
                                            rocketCard.selectIndex = 1
                                            parent.scale = 1.025
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
                                //player2 end
                                //player3
                                Rectangle{
                                    Layout.preferredHeight: parent.height
                                    Layout.fillWidth: true
                                    color: (rocketCard.selectIndex == 2) ? "#83ff05" : card_popUp.popUp_BtnColor
                                    border.color: "#5d7586"
                                    radius: 5
                                    property bool isHovered: false

                                    Text {
                                        text: "player3"
                                        font.family: "roboto"
                                        font.pixelSize: 10
                                        font.bold: true
                                        color: "black"
                                        anchors.centerIn:parent
                                        z: 1
                                    }

                                    Rectangle{
                                        width: parent.isHovered ? parent.width : 0
                                        height: parent.height
                                        color:(rocketCard.selectIndex == 2)? "transparent" : "#83ff05"
                                        radius: 5
                                        Behavior on width{
                                            NumberAnimation {
                                                duration: 100
                                                easing.type: Easing.InOutQuad
                                            }
                                        }
                                    }

                                    MouseArea{
                                        z: 2
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.isHovered = true
                                            parent.scale = 1.05
                                        }

                                        onExited: {
                                            parent.isHovered = false
                                            parent.scale = 1.0
                                        }

                                        onPressed: {
                                            rocketCard.selectIndex = 2
                                            parent.scale = 1.025
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
                                //player3 end
                                //player4
                                Rectangle{
                                    Layout.preferredHeight: parent.height
                                    Layout.fillWidth: true
                                    color: (rocketCard.selectIndex == 3) ? "#83ff05" : card_popUp.popUp_BtnColor
                                    border.color: "#5d7586"
                                    radius: 5
                                    property bool isHovered: false

                                    Text {
                                        text: "player4"
                                        font.family: "roboto"
                                        font.pixelSize: 10
                                        font.bold: true
                                        color: "black"
                                        anchors.centerIn:parent
                                        z: 1
                                    }

                                    Rectangle{
                                        width: parent.isHovered ? parent.width : 0
                                        height: parent.height
                                        color: (rocketCard.selectIndex == 3)? "transparent" : "#83ff05"
                                        radius: 5
                                        Behavior on width{
                                            NumberAnimation {
                                                duration: 100
                                                easing.type: Easing.InOutQuad
                                            }
                                        }
                                    }

                                    MouseArea{
                                        z: 2
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.isHovered = true
                                            parent.scale = 1.05
                                        }

                                        onExited: {
                                            parent.isHovered = false
                                            parent.scale = 1.0
                                        }

                                        onPressed: {
                                            rocketCard.selectIndex = 3
                                            parent.scale = 1.025
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
                                //player4 end
                            }

                            Turntable{
                                id: turntable
                                Layout.preferredHeight: parent.height / 4
                                Layout.preferredWidth: height
                                Layout.alignment: Qt.AlignCenter
                                afterRotate:{
                                    // 得到的值: rotatedIndex
                                    console.log(rotatedIndex + "天")
                                    console.log(rocketCard.selectIndex)
                                    event.rocketCardUseEntryPoint(rocketCard.selectIndex,rotatedIndex);
                                }
                            }

                            RowLayout{
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: 30

                                Rectangle{
                                    Layout.fillWidth: true
                                }

                                Rectangle{
                                    Layout.preferredHeight: 20
                                    Layout.preferredWidth: 50
                                    color: card_popUp.popUp_BtnColor
                                    border.color: "#05b4ff"
                                    radius: 5
                                    property bool isHovered: false

                                    Rectangle{
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
                                        text: "Use"
                                        font.bold: true
                                        font.family: "roboto"
                                        color: parent.isHovered ? "black" : "white"
                                        anchors.centerIn: parent
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: rocketCard.selectIndex !== -1
                                        onEntered: {
                                            parent.scale = 1.1
                                            parent.isHovered = true
                                        }
                                        onExited: {
                                            parent.scale = 1.0
                                            parent.isHovered = false
                                        }
                                        onPressed: {
                                            parent.scale = 1.05

                                        }
                                        onReleased: {
                                            parent.scale = 1.1
                                        }
                                        onClicked:{
                                            if (turntable.animationEnable) {
                                                turntable.rot += Math.random() * 360 + 5400;
                                            }
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
                                    Layout.preferredWidth: 5
                                }
                            }
                        }

                        Behavior on Layout.preferredHeight {
                            NumberAnimation {
                                duration: 200
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }
                }

                Behavior on Layout.preferredHeight {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            // Dice Card
            Rectangle {
                id: diceCard
                Layout.fillWidth: true
                Layout.preferredHeight: isOpen ? 200 : 40
                radius: 10
                color: playWindow.thirdaryColor
                border.color: playWindow.borderColor
                property bool isOpen: false
                clip: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 3
                    clip: true

                    RowLayout {
                        Layout.fillWidth: true

                        Rectangle {
                            Layout.fillWidth: true
                            color: "transparent"
                        }

                        Rectangle {
                            width: 30
                            height: 30
                            color: card_popUp.popUp_BtnColor
                            radius: 10
                            Text {
                                anchors.centerIn: parent
                                text: "◀"
                                color: "white"
                                transformOrigin: Item.Center
                                rotation: diceCard.isOpen ? -90 : 0
                                Behavior on rotation {
                                    NumberAnimation {
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    diceCard.isOpen = !diceCard.isOpen
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.preferredHeight: diceCard.isOpen ? 170 : 0
                        Layout.fillWidth: true
                        color: "transparent"
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            RowLayout{
                                Layout.fillWidth: true
                                Layout.preferredHeight: parent.height / 4
                                Text {
                                    text: "Move Distance:"
                                    font.family: "roboto"
                                    font.pixelSize: 15
                                    color: "white"
                                }
                                Rectangle{
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: parent.height
                                    color: playWindow.thirdaryColor
                                    border.color: playWindow.borderColor
                                    radius: 5
                                    Row{
                                        anchors.fill: parent
                                        anchors.margins: 5
                                        Rectangle{
                                            id: spinDistance_Rec
                                            width: parent.width * 4 / 5
                                            height: parent.height
                                            color: "transparent"
                                            property int moveDistance: 1
                                            Text {
                                                text: parent.moveDistance
                                                font.family: "roboto"
                                                font.pixelSize: 15
                                                color: "white"
                                                anchors.centerIn: parent
                                            }
                                        }
                                        Column{
                                            Rectangle{
                                                width: parent.parent.width / 5
                                                height: parent.parent.height / 2
                                                color: "transparent"
                                                Text {
                                                    text: "▲"
                                                    font.family: "roboto"
                                                    font.pixelSize: 10
                                                    color: "white"
                                                    anchors.centerIn: parent
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    enabled: spinDistance_Rec.moveDistance < 12 ? true : false
                                                    hoverEnabled: true
                                                    onEntered: {
                                                        parent.scale = 1.5
                                                    }
                                                    onExited: {
                                                        parent.scale = 1.0
                                                    }
                                                    onPressed: {
                                                        spinDistance_Rec.moveDistance++
                                                        parent.scale = 1.25
                                                    }
                                                    onReleased: {
                                                        parent.scale = 1.5
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
                                                width: parent.parent.width / 5
                                                height: parent.parent.height / 2
                                                color: "transparent"
                                                Text {
                                                    text: "▼"
                                                    font.family: "roboto"
                                                    font.pixelSize: 10
                                                    color: "white"
                                                    anchors.centerIn: parent
                                                }
                                                MouseArea{
                                                    anchors.fill: parent
                                                    enabled: spinDistance_Rec.moveDistance > 1 ? true : false
                                                    hoverEnabled: true
                                                    onEntered: {
                                                        parent.scale = 1.5
                                                    }
                                                    onExited: {
                                                        parent.scale = 1.0
                                                    }
                                                    onPressed: {
                                                        spinDistance_Rec.moveDistance--
                                                        parent.scale = 1.25
                                                    }
                                                    onReleased: {
                                                        parent.scale = 1.5
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
                                }
                            }
                            Rectangle{
                                Layout.fillHeight: true
                            }
                            RowLayout{
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: 30

                                Rectangle{
                                    Layout.fillWidth: true
                                }

                                Rectangle{
                                    Layout.preferredHeight: 20
                                    Layout.preferredWidth: 50
                                    color: card_popUp.popUp_BtnColor
                                    border.color: "#05b4ff"
                                    radius: 5
                                    property bool isHovered: false

                                    Rectangle{
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
                                        text: "Use"
                                        font.bold: true
                                        font.family: "roboto"
                                        color: parent.isHovered ? "black" : "white"
                                        anchors.centerIn: parent
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.scale = 1.1
                                            parent.isHovered = true
                                        }
                                        onExited: {
                                            parent.scale = 1.0
                                            parent.isHovered = false
                                        }
                                        onPressed: {
                                            parent.scale = 1.05

                                        }
                                        onReleased: {
                                            parent.scale = 1.1
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
                                    Layout.preferredWidth: 5
                                }
                            }
                        }

                        Behavior on Layout.preferredHeight {
                            NumberAnimation {
                                duration: 200
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }
                }

                Behavior on Layout.preferredHeight {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            // Remove Card
            Rectangle {
                id: removeCard
                Layout.fillWidth: true
                Layout.preferredHeight: isOpen ? 200 : 40
                radius: 10
                color: playWindow.thirdaryColor
                border.color: playWindow.borderColor
                property bool isOpen: false
                clip: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 3
                    clip: true

                    RowLayout {
                        Layout.fillWidth: true

                        Rectangle {
                            Layout.fillWidth: true
                            color: "transparent"
                        }

                        Rectangle {
                            width: 30
                            height: 30
                            color: card_popUp.popUp_BtnColor
                            radius: 10
                            Text {
                                anchors.centerIn: parent
                                text: "◀"
                                color: "white"
                                transformOrigin: Item.Center
                                rotation: removeCard.isOpen ? -90 : 0
                                Behavior on rotation {
                                    NumberAnimation {
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    removeCard.isOpen = !removeCard.isOpen
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.preferredHeight: removeCard.isOpen ? 170 : 0
                        Layout.fillWidth: true
                        color: "transparent"
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            RowLayout{
                                Layout.preferredHeight: parent.height / 5
                                Layout.fillWidth: true
                                Text {
                                    text: "choose place you want to remove:"
                                    font.family: "roboto"
                                    font.pixelSize: 10
                                    color: "white"
                                }
                                ComboBox {
                                    id: removeCoordinate
                                    Layout.fillWidth: true
                                    model: ["1", "2", "3", "4", "5", "6"]
                                    onCurrentIndexChanged: {
                                        console.log("Selected:", currentText)
                                    }
                                }
                            }
                            Rectangle{
                                Layout.fillHeight: true
                            }
                            RowLayout{
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: 30

                                Rectangle{
                                    Layout.fillWidth: true
                                }

                                Rectangle{
                                    Layout.preferredHeight: 20
                                    Layout.preferredWidth: 50
                                    color: card_popUp.popUp_BtnColor
                                    border.color: "#05b4ff"
                                    radius: 5
                                    property bool isHovered: false

                                    Rectangle{
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
                                        text: "Use"
                                        font.bold: true
                                        font.family: "roboto"
                                        color: parent.isHovered ? "black" : "white"
                                        anchors.centerIn: parent
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.scale = 1.1
                                            parent.isHovered = true
                                        }
                                        onExited: {
                                            parent.scale = 1.0
                                            parent.isHovered = false
                                        }
                                        onPressed: {
                                            parent.scale = 1.05
                                            console.log(removeCoordinate.currentText)
                                        }
                                        onReleased: {
                                            parent.scale = 1.1
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
                                    Layout.preferredWidth: 5
                                }
                            }
                        }

                        Behavior on Layout.preferredHeight {
                            NumberAnimation {
                                duration: 200
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }
                }

                Behavior on Layout.preferredHeight {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            // RoadBlock Card
            Rectangle {
                id: roadBlockCard
                Layout.fillWidth: true
                Layout.preferredHeight: isOpen ? 200 : 40
                radius: 10
                color: playWindow.thirdaryColor
                border.color: playWindow.borderColor
                property bool isOpen: false
                clip: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 3
                    clip: true

                    RowLayout {
                        Layout.fillWidth: true

                        Rectangle {
                            Layout.fillWidth: true
                            color: "transparent"
                        }

                        Rectangle {
                            width: 30
                            height: 30
                            color: card_popUp.popUp_BtnColor
                            radius: 10
                            Text {
                                anchors.centerIn: parent
                                text: "◀"
                                color: "white"
                                transformOrigin: Item.Center
                                rotation: roadBlockCard.isOpen ? -90 : 0
                                Behavior on rotation {
                                    NumberAnimation {
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    roadBlockCard.isOpen = !roadBlockCard.isOpen
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.preferredHeight: roadBlockCard.isOpen ? 170 : 0
                        Layout.fillWidth: true
                        color: "transparent"
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            RowLayout{
                                Layout.preferredHeight: parent.height / 5
                                Layout.fillWidth: true
                                Text {
                                    text: "choose place you want to block:"
                                    font.family: "roboto"
                                    font.pixelSize: 10
                                    color: "white"
                                }
                                ComboBox {
                                    id: blockCoordinate
                                    Layout.fillWidth: true
                                    model: ["1", "2", "3", "4", "5", "6"]
                                    onCurrentIndexChanged: {
                                        console.log("Selected:", currentText)
                                    }
                                }
                            }
                            Rectangle{
                                Layout.fillHeight: true
                            }
                            RowLayout{
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: 30

                                Rectangle{
                                    Layout.fillWidth: true
                                }

                                Rectangle{
                                    Layout.preferredHeight: 20
                                    Layout.preferredWidth: 50
                                    color: card_popUp.popUp_BtnColor
                                    border.color: "#05b4ff"
                                    radius: 5
                                    property bool isHovered: false

                                    Rectangle{
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
                                        text: "Use"
                                        font.bold: true
                                        font.family: "roboto"
                                        color: parent.isHovered ? "black" : "white"
                                        anchors.centerIn: parent
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        enabled: true
                                        onEntered: {
                                            parent.scale = 1.1
                                            parent.isHovered = true
                                        }
                                        onExited: {
                                            parent.scale = 1.0
                                            parent.isHovered = false
                                        }
                                        onPressed: {
                                            parent.scale = 1.05
                                            console.log(blockCoordinate.currentText)
                                        }
                                        onReleased: {
                                            parent.scale = 1.1
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
                                    Layout.preferredWidth: 5
                                }
                            }
                        }

                        Behavior on Layout.preferredHeight {
                            NumberAnimation {
                                duration: 200
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }
                }

                Behavior on Layout.preferredHeight {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            // Event Card
            Rectangle {
                id: eventCard
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                color: card_popUp.popUp_BtnColor
                border.color: playWindow.borderColor
                radius: 5
                property bool isHovered: false

                Rectangle{
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
                    text: "Event Card"
                    font.bold: true
                    font.family: "roboto"
                    color: parent.isHovered ? "black" : "white"
                    anchors.centerIn: parent
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true
                    onEntered: {
                        parent.scale = 1.05
                        parent.isHovered = true
                    }
                    onExited: {
                        parent.scale = 1.0
                        parent.isHovered = false
                    }
                    onPressed: {
                        parent.scale = 1.025
                        console.log(123)
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

    SequentialAnimation{
        id: card_popUp_CloseAniamtion
        NumberAnimation {
            target: card_popUp
            property: "height"
            to : 3
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: card_popUp
            property: "width"
            to : 0
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: card_popUp
            property: "height"
            to : 0
            duration: 1
            easing.type: Easing.InOutQuad
        }
        ScriptAction{
            script: {
                card_popUp.close()
            }
        }
    }
    SequentialAnimation{
        id: card_popUp_OpenAniamtion
        ScriptAction{
            script: {
                card_popUp.open()
            }
        }
        NumberAnimation {
            target: card_popUp
            property: "height"
            to : 3
            duration: 1
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: card_popUp
            property: "width"
            to : 300
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: card_popUp
            property: "height"
            to : 500
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
}
