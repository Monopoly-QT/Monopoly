import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects

import "../Resources"

Window {
    width: 1280
    height: 720
    visible: true
    // visibility: Window.FullScreen

    Rectangle{
        id:playWindow
        color:playWindow.backGroundColor
        anchors.fill: parent
        property color backGroundColor: "#3c3c3c"
        property color secondaryColor: "#454545"
        property color thirdaryColor: "#505050"
        property color borderColor: "#ff9300"
        property color hoverColor: "#808080"
        property color pressColor: "#747474"
        property int dicePoint: 0
        Rectangle{
            id: movePoint
            height: 10
            width: 10
            color: event.movePoint.displayColor
            x:map_Grid.coordinateList[0].posX
            y:map_Grid.coordinateList[0].posY
            z: 2
            radius: width/2
            visible: event.movePoint.isvisable
            property int moveDuaration: 0

            Behavior on x{
                NumberAnimation {
                    duration: movePoint.moveDuaration
                    easing.type: Easing.InOutQuad
                }
            }

            Behavior on y{
                NumberAnimation {
                    duration: movePoint.moveDuaration
                    easing.type: Easing.InOutQuad
                }
            }

            SequentialAnimation{
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

        RowLayout{
            anchors.fill: parent
            Rectangle{
                Layout.fillHeight: true
                Layout.fillWidth: true
                color:"transparent"
                Rectangle{
                    anchors.fill: parent
                    anchors.margins: 10
                    color:"transparent"
                    GridLayout{
                        id: map_Grid
                        property var coordinateList: []
                        anchors.fill: parent
                        columns: 11
                        columnSpacing: 0
                        rowSpacing: 0
                        property int order: 1
                        Repeater{
                            id: mapGenerate
                            model: event.mapList
                            Rectangle{
                                Layout.preferredHeight: parent.height / 11
                                Layout.preferredWidth: parent.width / 11
                                color: playWindow.secondaryColor
                                border.color: playWindow.borderColor
                                border.width: 1
                                opacity: model.isDisplay ? 1 : 0

                                ColumnLayout{
                                    anchors.fill: parent
                                    spacing: 0
                                    //order and name
                                    Rectangle{
                                        Layout.preferredHeight: parent.height / 3
                                        Layout.preferredWidth: parent.width
                                        Layout.alignment: Qt.AlignTop
                                        color: model.displayColor
                                        border.color: playWindow.borderColor
                                        RowLayout{
                                            anchors.fill: parent
                                            anchors.margins: 5
                                            spacing: 0
                                            //land order
                                            Text {
                                                text: model.order+"."
                                                color: "white"
                                                font.bold: true
                                                font.family: "roboto"
                                                font.pixelSize: (parent.height/ 1.2 < parent.height / 1.2) ? parent.height/ 1.2 : parent.height / 1.2
                                            }

                                            //land name
                                            Rectangle{
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

                                                MouseArea{
                                                    anchors.fill: parent
                                                    hoverEnabled: true
                                                    onEntered:{
                                                        model.showTranslation = true;
                                                    }

                                                    onExited:{
                                                        model.showTranslation = false;
                                                    }
                                                }
                                            }

                                        }
                                    }

                                    Rectangle{

                                        Layout.preferredHeight: parent.height / 3 * 2
                                        Layout.preferredWidth: parent.width
                                        color: "transparent"

                                        property real centerX: x + width / 2
                                        property real centerY: y + height / 2
                                        property var pt

                                        RowLayout{
                                            anchors.fill: parent
                                            anchors.margins: 5
                                            //player stay
                                            ColumnLayout{
                                                Layout.preferredHeight: parent.height
                                                Layout.preferredWidth: parent.width / 3
                                                spacing: 0

                                                //player1
                                                Rectangle{
                                                    Layout.fillHeight: true
                                                    Layout.fillWidth: true
                                                    color: "transparent"
                                                    Rectangle{
                                                        anchors.centerIn: parent
                                                        height: parent.height / 2
                                                        width: height
                                                        radius: width / 2
                                                        color: "#ff1700"
                                                        visible: model.playerStay[0] === 1 ? true : false
                                                    }
                                                }
                                                //player2
                                                Rectangle{
                                                    Layout.fillHeight: true
                                                    Layout.fillWidth: true
                                                    color: "transparent"
                                                    Rectangle{
                                                        anchors.centerIn: parent
                                                        height: parent.height / 2
                                                        width: height
                                                        radius: width / 2
                                                        color: "#009aff"
                                                        visible: model.playerStay[1] === 1 ? true : false
                                                    }
                                                }
                                                //player3
                                                Rectangle{
                                                    Layout.fillHeight: true
                                                    Layout.fillWidth: true
                                                    color: "transparent"
                                                    Rectangle{
                                                        anchors.centerIn: parent
                                                        height: parent.height / 2
                                                        width: height
                                                        radius: width / 2
                                                        color: "#0fff00"
                                                        visible: model.playerStay[2] === 1 ? true : false
                                                    }
                                                }
                                                //player4
                                                Rectangle{
                                                    Layout.fillHeight: true
                                                    Layout.fillWidth: true
                                                    color: "transparent"
                                                    Rectangle{
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

                                            ColumnLayout{
                                                Layout.preferredHeight: parent.height
                                                Layout.preferredWidth: parent.width * 2 / 3
                                                spacing: 0

                                                RowLayout{
                                                    Layout.fillHeight: true
                                                    Layout.fillWidth: true
                                                    visible: (model.isDisplayBuilding[0] === 1 || model.isDisplayBuilding[1] === 1) ? true :false
                                                    spacing: 1
                                                    //house1
                                                    Rectangle{
                                                        Layout.fillHeight: true
                                                        Layout.fillWidth: true
                                                        color: "transparent"
                                                        visible: model.isDisplayBuilding[0] === 1 ? true : false
                                                        Image {
                                                            anchors.centerIn: parent
                                                            height: (parent.height > parent.width)? parent.width : parent.height
                                                            width: (parent.height > parent.width)? parent.width : parent.height
                                                            source: "qrc:/images/house.png"
                                                        }
                                                    }
                                                    //house1 end
                                                    //house2
                                                    Rectangle{
                                                        Layout.fillHeight: true
                                                        Layout.fillWidth: true
                                                        color: "transparent"
                                                        visible: model.isDisplayBuilding[1] === 1 ? true : false
                                                        Image {
                                                            anchors.centerIn: parent
                                                            height: (parent.height > parent.width)? parent.width : parent.height
                                                            width: (parent.height > parent.width)? parent.width : parent.height
                                                            source: "qrc:/images/house.png"
                                                        }
                                                    }
                                                    //house2 end
                                                }

                                                RowLayout{
                                                    Layout.fillHeight: true
                                                    Layout.fillWidth: true
                                                    spacing: 1
                                                    visible: (model.isDisplayBuilding[2] === 1 || model.isDisplayBuilding[3] === 1) ? true :false
                                                    //house3
                                                    Rectangle{
                                                        Layout.fillHeight: true
                                                        Layout.fillWidth: true
                                                        color: "transparent"
                                                        visible: model.isDisplayBuilding[2] === 1 ? true : false
                                                        Image {
                                                            anchors.centerIn: parent
                                                            height: (parent.height > parent.width)? parent.width : parent.height
                                                            width: (parent.height > parent.width)? parent.width : parent.height
                                                            source: "qrc:/images/house.png"
                                                        }
                                                    }
                                                    //house3 end
                                                    //building
                                                    Rectangle{
                                                        Layout.fillHeight: true
                                                        Layout.fillWidth: true
                                                        color: "transparent"
                                                        visible: model.isDisplayBuilding[3] === 1 ? true : false
                                                        Image {
                                                            anchors.centerIn: parent
                                                            height: (parent.height > parent.width)? parent.width : parent.height
                                                            width: (parent.height > parent.width)? parent.width : parent.height
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
                                                    if(model.isDisplay === true){
                                                        parent.pt = mapToItem(null, parent.centerX, parent.centerY);
                                                        console.log("Correct global position:",parent.pt.x, parent.pt.y);
                                                        // map_Grid.coordinateList.push({posX:parent.pt.x,posY:parent.pt.y})
                                                        event.addMapPosXandPosY(parent.pt.x, parent.pt.y)
                                                    }
                                                    else{
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
                                        onWidthChanged:{
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

            Rectangle{
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width/5
                color:playWindow.secondaryColor
                ColumnLayout{
                    id:stateColumn
                    anchors.fill: parent
                    anchors.margins: 10

                    Rectangle{
                        id: stateContainer
                        Layout.preferredHeight: parent.height / 7.5
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
                                Layout.preferredHeight: stateContainer.height / 2
                                Layout.preferredWidth:  stateContainer.width
                                Layout.alignment: Qt.AlignTop
                                border.color: playWindow.borderColor
                                color: "transparent"
                                topLeftRadius: 10
                                topRightRadius: 10
                                clip: true
                                Text {
                                    id: playerNum
                                    text: "playerNum"
                                    font.bold: true
                                    font.pixelSize: 20
                                    font.family: "roboto"
                                    color: "white"
                                    anchors.centerIn: parent
                                }
                            }
                            RowLayout{
                                id: moneyContainer_Rowlayout
                                Layout.preferredHeight: stateContainer.height / 2
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
                                        text: "1000000"
                                        font.bold: true
                                        font.pixelSize: 15
                                        font.family: "roboto"
                                        color: "white"
                                    }
                                }
                            }
                        }
                    }

                    RowLayout{
                        Layout.preferredHeight: parent.height / 20
                        Layout.preferredWidth: parent.width

                        Rectangle{
                            Layout.fillWidth: true
                        }

                        //card
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
                                enabled: true
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
                                        card_popUp_OpenAniamtion.start()
                                    }
                                    else{
                                        card_popUp_CloseAniamtion.start()
                                    }
                                }
                                onReleased: {
                                    cardImage.scale = 1.25
                                }
                            }
                        }

                        //cheat command
                        Rectangle{
                            id: cheatImage_Rec
                            Layout.preferredWidth: parent.width / 5
                            Layout.preferredHeight: parent.height
                            color: "transparent"
                            radius: 10
                            property bool isActivity: false

                            Image {
                                id: cheatImage
                                height: (parent.width < parent.height) ? parent.width * 0.8 : parent.height * 0.8
                                width: (parent.width < parent.height) ? parent.width * 0.8 : parent.height * 0.8
                                anchors.centerIn: parent
                                source: (parent.isActivity) ? "qrc:/images/cheat_1.png" : "qrc:/images/cheat.png"

                                Behavior on scale {
                                    NumberAnimation {
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }

                            }

                            MouseArea{
                                enabled: true
                                hoverEnabled: true
                                anchors.fill: parent
                                onEntered: {
                                    cheatImage.scale = 1.25
                                }
                                onExited: {
                                    cheatImage.scale = 1.0
                                }
                                onPressed: {
                                    parent.isActivity = !parent.isActivity
                                    cheatImage.scale = 1.15
                                }
                                onReleased: {
                                    cheatImage.scale = 1.25
                                }
                            }
                        }
                    }

                    Button{
                        Layout.preferredHeight: parent.height/30
                        Layout.preferredWidth: parent.width
                        property int index: 0
                        onClicked: {
                            event.movePointAnimator()
                        }
                    }

                    Rectangle{
                        Layout.fillHeight: true
                    }

                    Rectangle{
                        id: cheatCommandLine_Rec
                        Layout.preferredHeight: (cheatImage_Rec.isActivity) ? parent.height / 12.5 : 0
                        Layout.preferredWidth: parent.width
                        color:playWindow.thirdaryColor
                        border.color: playWindow.borderColor
                        radius: 10
                        clip: true

                        ColumnLayout{
                            anchors.fill: parent
                            anchors.margins: 10
                            TextField{
                                id: cheatCommandLine_Textfield
                                Layout.preferredHeight: parent.height/3
                                Layout.fillWidth: true
                                placeholderText: "Insert command"
                            }
                            RowLayout{
                                Layout.preferredHeight: parent.height/3
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
                                        text: "execute"
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
                                        text: "clear"
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

                    Rectangle{
                        id: diceContainer
                        Layout.preferredHeight: parent.height/10
                        Layout.preferredWidth: parent.width
                        color:playWindow.thirdaryColor
                        border.color: playWindow.borderColor
                        radius: 10
                        property bool isHovered: false
                        property bool isPressed: false
                        MouseArea{
                            id: diceBtn
                            anchors.fill: parent
                            hoverEnabled: true

                            onEntered: {
                                parent.scale = 1.015
                                diceContainer.isHovered = true
                            }
                            onExited: {
                                parent.scale = 1.0
                                diceContainer.isHovered = false
                            }
                            onPressed: {
                                parent.scale = 1.0
                                diceContainer.isPressed = true
                                if(diceTimer.running === false)
                                    diceTimer.start()
                            }
                            onReleased: {
                                parent.scale = 1.015
                                diceContainer.isPressed = false
                            }
                        }
                        Timer {
                                id: diceTimer
                                interval: 50
                                repeat: true
                                running: false

                                property int time: 1000

                                onTriggered: {
                                    time = time-50
                                    diceA.rollDice(114514)
                                    diceB.rollDice(0)
                                    if (time <= 0) {
                                        diceTimer.stop();
                                        time = 1000;
                                        playWindow.dicePoint = diceA.dicePoint + diceB.dicePoint + 2
                                        event.moveEntryPoint(playWindow.dicePoint)
                                    }
                                }
                            }
                        Behavior on scale{
                            NumberAnimation {
                                duration: 100
                                easing.type: Easing.InOutQuad
                            }
                        }

                        Rectangle{
                            height: parent.height
                            width: diceContainer.isHovered ? parent.width : 0
                            radius: parent.radius
                            color: diceContainer.isPressed ? playWindow.pressColor : playWindow.hoverColor
                            z: 1
                            Behavior on width{
                                NumberAnimation {
                                    duration: 100
                                    easing.type: Easing.InOutQuad
                                }
                            }
                            Behavior on color {
                                ColorAnimation {
                                    duration: 200
                                }
                            }
                        }

                        RowLayout{
                            anchors.fill:parent
                            anchors.margins: 10
                            z:2
                            Rectangle{
                                Layout.fillWidth: true
                            }
                            //diceA
                            Rectangle{
                                id:rec_diceA
                                Layout.preferredHeight: parent.height
                                Layout.preferredWidth: height
                                color:"white"
                                radius: 5
                                ColumnLayout{
                                    anchors.fill: parent
                                    anchors.margins: 5
                                    RowLayout{
                                        Layout.preferredHeight: parent.height/3
                                        Layout.preferredWidth: parent.width

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                        Rectangle{//dicePointA
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceAShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointB
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceBShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointC
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceCShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }
                                    }
                                    RowLayout{
                                        Layout.preferredHeight: parent.height/3
                                        Layout.preferredWidth: parent.width

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                        Rectangle{//dicePointD
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceDShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                    }
                                    RowLayout{
                                        Layout.preferredHeight: parent.height/3
                                        Layout.preferredWidth: parent.width

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                        Rectangle{//dicePointE
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceEShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointF
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceFShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointG
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceA.DiceGShow? diceA.pointColor : "white"
                                            radius: width/2
                                        }

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }
                                    }
                                }
                            }
                            //diceB
                            Rectangle{
                                id:rec_diceB
                                Layout.preferredHeight: parent.height
                                Layout.preferredWidth: height
                                color:"white"
                                radius: 5
                                ColumnLayout{
                                    anchors.fill: parent
                                    anchors.margins: 5
                                    RowLayout{
                                        Layout.preferredHeight: parent.height/3
                                        Layout.preferredWidth: parent.width

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                        Rectangle{//dicePointA
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceAShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointB
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceBShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointC
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceCShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                    }
                                    RowLayout{
                                        Layout.preferredHeight: parent.height/3
                                        Layout.preferredWidth: parent.width

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                        Rectangle{//dicePointD
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceDShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                    }
                                    RowLayout{
                                        Layout.preferredHeight: parent.height/3
                                        Layout.preferredWidth: parent.width

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }

                                        Rectangle{//dicePointE
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceEShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointF
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceFShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }
                                        Rectangle{//dicePointG
                                            Layout.preferredHeight: width
                                            Layout.preferredWidth: parent.width/5
                                            color: diceB.DiceGShow? diceB.pointColor : "white"
                                            radius: width/2
                                        }

                                        Rectangle{
                                            Layout.fillWidth: true
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                Layout.fillWidth: true
                            }
                        }
                    }
                }
            }
        }
    }

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
                                anchors.margins: 0
                                RowLayout{
                                    Layout.preferredWidth: parent.width
                                    Layout.preferredHeight: 10
                                    Text {
                                        text: "Target"
                                        font.family: "roboto"
                                        font.pixelSize: 10
                                        color: "white"
                                    }
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
                                                parent.scale = 1.1
                                            }

                                            onExited: {
                                                parent.isHovered = false
                                                parent.scale = 1.0
                                            }

                                            onPressed: {
                                                rocketCard.selectIndex = 0
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
                                                parent.scale = 1.1
                                            }

                                            onExited: {
                                                parent.isHovered = false
                                                parent.scale = 1.0
                                            }

                                            onPressed: {
                                                rocketCard.selectIndex = 1
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
                                                parent.scale = 1.1
                                            }

                                            onExited: {
                                                parent.isHovered = false
                                                parent.scale = 1.0
                                            }

                                            onPressed: {
                                                rocketCard.selectIndex = 2
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
                                                parent.scale = 1.1
                                            }

                                            onExited: {
                                                parent.isHovered = false
                                                parent.scale = 1.0
                                            }

                                            onPressed: {
                                                rocketCard.selectIndex = 3
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
                                    //player4 end
                                }

                                Turntable{
                                    id: turntable
                                    Layout.preferredHeight: parent.height / 3
                                    Layout.preferredWidth: height
                                    Layout.alignment: Qt.AlignCenter
                                    afterRotate:{
                                        // 得到的值: rotatedIndex
                                        console.log(rotatedIndex + "天")
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

    Connections{
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
    }
}
