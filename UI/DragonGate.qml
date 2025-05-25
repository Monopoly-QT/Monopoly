import QtQuick
import QtQuick.Controls.Basic
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import QtQuick.Effects

Page {
    id: dragonGateRoot
    visible: true
    title: qsTr("Dragon Gate")

    property bool gameStarted: false
    property bool gameEnded: false
    property int betAmount: 100
    property int guessType: 0 // 1: 不同 2: 相同
    property int result: 0 // 1: 輸 2: 贏 3: 撞柱

    // 更新主題色配色
    property color primaryColor: "#FF5252"        // 鮮豔的紅色作為主色調
    property color secondaryColor: "#FFAB40"      // 橙色作為輔助色
    property color accentColor: "#40C4FF"         // 亮藍色作為強調色
    property color warningColor: "#FFEB3B"        // 黃色作為警告色
    property color errorColor: "#FF1744"          // 紅色作為錯誤色
    property color successColor: "#00E676"        // 綠色作為成功色
    property color surfaceColor: "#121212"        // 深灰色作為背景
    property color cardColor: "#1E1E1E"           // 卡片背景色

    Connections {
        target: gameClass
        onUpdateState: {
            event.updateState();
        }
    }

    Item {
        width: parent.width
        height: parent.height

        // 背景設計
        Rectangle {
            id: background
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.darker(surfaceColor, 1.2) }
                GradientStop { position: 1.0; color: surfaceColor }
            }
        }

        // 背景裝飾元素
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.lineWidth = 1;
                ctx.strokeStyle = Qt.rgba(1, 1, 1, 0.03);

                // 繪製網格狀裝飾
                for (var i = 0; i < width; i += 30) {
                    ctx.beginPath();
                    ctx.moveTo(i, 0);
                    ctx.lineTo(i, height);
                    ctx.stroke();
                }

                for (var j = 0; j < height; j += 30) {
                    ctx.beginPath();
                    ctx.moveTo(0, j);
                    ctx.lineTo(width, j);
                    ctx.stroke();
                }
            }
        }

        // 頂部裝飾條
        Rectangle {
            width: parent.width
            height: 4
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: primaryColor }
                GradientStop { position: 0.5; color: secondaryColor }
                GradientStop { position: 1.0; color: accentColor }
            }
            anchors.top: parent.top
        }

        Column {
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            topPadding: 30
            spacing: 20

            Item {
                id: titleText
                width: parent.width
                anchors.topMargin: 10
                height: title.height + 20

                Text {
                    id: title
                    text: "Dragon Gate"
                    font.pixelSize: 46
                    font.bold: true
                    font.family: "Microsoft YaHei"
                    color: "#FFFFFF"
                    anchors.horizontalCenter: parent.horizontalCenter
                    topPadding: 10

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowColor: Qt.alpha(primaryColor, 0.6)
                        shadowHorizontalOffset: 0
                        shadowVerticalOffset: 2
                        shadowBlur: 14
                        shadowOpacity: 0.8
                    }
                }

                Rectangle {
                    id: moneyDisplay
                    width: 180
                    height: 40
                    radius: 20
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: Qt.alpha(primaryColor, 0.1) }
                        GradientStop { position: 1.0; color: Qt.alpha(secondaryColor, 0.15) }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)
                    anchors.margins: 10
                    anchors.right: parent.right

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 8

                        Rectangle {
                            width: 24
                            height: 24
                            radius: 12
                            color: Qt.alpha(secondaryColor, 0.2)
                            border.width: 2
                            border.color: secondaryColor

                            Text {
                                anchors.centerIn: parent
                                text: "$"
                                color: secondaryColor
                                font.pixelSize: 14
                                font.bold: true
                            }
                        }

                        Text {
                            text: "Balance"
                            color: "#e0e0e0"
                            font.pixelSize: 14
                            font.bold: true
                        }

                        Text {
                            text: playerClass.money
                            color: secondaryColor
                            font.pixelSize: 16
                            font.bold: true
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignRight
                        }
                    }
                }
            }

            Item {
                id: gameArea
                width: parent.width * 0.8
                height: parent.height * 0.4
                anchors.horizontalCenter: parent.horizontalCenter

                Rectangle {
                    width: parent.width
                    height: parent.height
                    anchors.fill: parent
                    anchors.margins: -20
                    color: Qt.rgba(1, 1, 1, 0.02)
                    radius: 16
                    border.width: 1
                    border.color: Qt.rgba(1, 1, 1, 0.05)
                }

                Row {
                    width: parent.width
                    height: parent.height
                    anchors.centerIn: parent
                    spacing: 30

                    Rectangle {
                        id: leftCardRect
                        width: 130
                        height: 190
                        radius: 10
                        color: cardColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 40

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 5
                            radius: 6
                            color: "transparent"
                            border.width: 1
                            border.color: Qt.alpha(primaryColor, 0.3)
                        }

                        Rectangle {
                            anchors.centerIn: parent
                            width: 90
                            height: 90
                            radius: 45
                            color: Qt.alpha(primaryColor, 0.1)
                            border.width: 1
                            border.color: Qt.alpha(primaryColor, 0.2)
                        }

                        Text {
                            anchors.centerIn: parent
                            text: gameClass.firstNumber === -1 ? "?" : gameClass.firstNumber
                            color: primaryColor
                            font.pixelSize: 52
                            font.bold: true
                            font.family: "Arial"
                        }

                        Text {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.margins: 10
                            text: gameClass.firstNumber === -1 ? "?" : gameClass.firstNumber
                            color: Qt.alpha(primaryColor, 0.7)
                            font.pixelSize: 18
                            font.bold: true
                        }

                        Text {
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 10
                            text: gameClass.firstNumber === -1 ? "?" : gameClass.firstNumber
                            color: Qt.alpha(primaryColor, 0.7)
                            font.pixelSize: 18
                            font.bold: true
                        }

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: "#000000"
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 4
                            shadowBlur: 12
                            shadowOpacity: 0.4
                        }
                    }

                    Rectangle {
                        id: rightCardRect
                        width: 130
                        height: 190
                        radius: 10
                        color: cardColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 40

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 5
                            radius: 6
                            color: "transparent"
                            border.width: 1
                            border.color: Qt.alpha(primaryColor, 0.3)
                        }

                        Rectangle {
                            anchors.centerIn: parent
                            width: 90
                            height: 90
                            radius: 45
                            color: Qt.alpha(primaryColor, 0.1)
                            border.width: 1
                            border.color: Qt.alpha(primaryColor, 0.2)
                        }

                        Text {
                            anchors.centerIn: parent
                            text: gameClass.secondNumber === -1 ? "?" : gameClass.secondNumber
                            color: primaryColor
                            font.pixelSize: 52
                            font.bold: true
                            font.family: "Arial"
                        }

                        Text {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.margins: 10
                            text: gameClass.secondNumber === -1 ? "?" : gameClass.secondNumber
                            color: Qt.alpha(primaryColor, 0.7)
                            font.pixelSize: 18
                            font.bold: true
                        }

                        Text {
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 10
                            text: gameClass.secondNumber === -1 ? "?" : gameClass.secondNumber
                            color: Qt.alpha(primaryColor, 0.7)
                            font.pixelSize: 18
                            font.bold: true
                        }

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: "#000000"
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 4
                            shadowBlur: 12
                            shadowOpacity: 0.4
                        }
                    }

                    Rectangle {
                        id: resultCardRect
                        width: 130
                        height: 190
                        radius: 10
                        color: cardColor
                        anchors.centerIn: parent

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 5
                            radius: 6
                            color: "transparent"
                            border.width: 2
                            border.color: gameEnded ?
                                (result === 2 ? successColor :
                                        result === 1 ? warningColor : errorColor) :
                                (gameStarted ? accentColor : Qt.alpha(primaryColor, 0.3))
                        }

                        Rectangle {
                            anchors.centerIn: parent
                            width: 90
                            height: 90
                            radius: 45
                            color: gameEnded ?
                                (result === 2 ? Qt.alpha(successColor, 0.1) :
                                        result === 1 ? Qt.alpha(warningColor, 0.1) : Qt.alpha(errorColor, 0.1)) :
                                Qt.alpha(accentColor, 0.1)
                            border.width: 2
                            border.color: gameEnded ?
                                (result === 2 ? Qt.alpha(successColor, 0.3) :
                                        result === 1 ? Qt.alpha(warningColor, 0.3) : Qt.alpha(errorColor, 0.3)) :
                                Qt.alpha(accentColor, 0.3)
                        }

                        Text {
                            anchors.centerIn: parent
                            text: gameClass.thirdNumber === -1 ? "?" : gameClass.thirdNumber
                            color: gameEnded ?
                                (result === 1 ? successColor :
                                        result === 2 ? warningColor : errorColor) :
                                accentColor
                            font.pixelSize: 52
                            font.bold: true
                            font.family: "Arial"
                        }

                        Text {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.margins: 10
                            text: gameClass.thirdNumber === -1 ? "?" : gameClass.thirdNumber
                            color: gameEnded ?
                                (result === 1 ? Qt.alpha(successColor, 0.7) :
                                        result === 2 ? Qt.alpha(warningColor, 0.7) : Qt.alpha(errorColor, 0.7)) :
                                Qt.alpha(accentColor, 0.7)
                            font.pixelSize: 18
                            font.bold: true
                        }

                        Text {
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 10
                            text: gameClass.thirdNumber === -1 ? "?" : gameClass.thirdNumber
                            color: gameEnded ?
                                (result === 1 ? Qt.alpha(successColor, 0.7) :
                                        result === 2 ? Qt.alpha(warningColor, 0.7) : Qt.alpha(errorColor, 0.7)) :
                                Qt.alpha(accentColor, 0.7)
                            font.pixelSize: 18
                            font.bold: true
                        }

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: gameStarted && !gameEnded ?
                                accentColor :
                                (gameEnded ?
                                    (result === 1 ? successColor :
                                            result === 2 ? warningColor : errorColor) :
                                    "#000000")
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 0
                            shadowBlur: gameStarted && !gameEnded ? 20 : 12
                            shadowOpacity: gameStarted && !gameEnded ? 0.5 : 0.4
                        }

                        MouseArea {
                            anchors.fill: parent
                            enabled: gameStarted && !gameEnded
                            hoverEnabled: enabled
                            onEntered: {
                                if (enabled) {
                                    resultCardRect.scale = 1.05
                                }
                            }
                            onExited: {
                                resultCardRect.scale = 1.0
                            }
                        }

                        Behavior on scale {
                            NumberAnimation {
                                duration: 200
                                easing.type: Easing.OutQuad
                            }
                        }
                    }
                }
            }

            Item {
                height: 20
                width: 10
            }

            SpinBox {
                id: betSpinBox
                from: 0
                to: playerClass.money
                stepSize: 100
                enabled: !gameStarted || gameEnded
                width: parent.width * 0.4
                height: 40
                value: betAmount
                anchors.horizontalCenter: parent.horizontalCenter

                onValueChanged: {
                    betAmount = value
                }

                contentItem: Text {
                    text: "Bet Amount: $" + betAmount
                    font.pixelSize: 16
                    font.bold: true
                    color: "#FFFFFF"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                }

                background: Rectangle {
                    radius: 8
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#2A2A2A" }
                        GradientStop { position: 1.0; color: "#3D3D3D" }
                    }
                    border.width: 1
                    border.color: "#555555"

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowColor: "#000000"
                        shadowHorizontalOffset: 0
                        shadowVerticalOffset: 3
                        shadowBlur: 8
                        shadowOpacity: 0.3
                    }
                }

                up.indicator: Rectangle{
                    x: betSpinBox.mirrored ? 0 : parent.width - width
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: Qt.alpha(primaryColor, 0.1) }
                        GradientStop { position: 1.0; color: Qt.alpha(secondaryColor, 0.15) }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)

                    Text {
                        text: "+"
                        font.pixelSize: betSpinBox.font.pixelSize*1.5
                        color: "#ffffff"
                        font.bold: true
                        anchors.fill: parent
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                down.indicator: Rectangle{
                    x: 0
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: Qt.alpha(primaryColor, 0.1) }
                        GradientStop { position: 1.0; color: Qt.alpha(secondaryColor, 0.15) }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)

                    Text {
                        text: "-"
                        font.pixelSize: betSpinBox.font.pixelSize*1.5
                        color: "#ffffff"
                        font.bold: true
                        anchors.fill: parent
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: Rectangle {
                        width: betSpinBox.width
                        height: betSpinBox.height
                        radius: 8
                    }
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30
                visible: !gameStarted || gameEnded

                Button {
                    id: backButton
                    text: "Back"
                    width: 120
                    height: 46
                    visible: gameEnded

                    contentItem: Text {
                        text: backButton.text
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.bold: true
                        font.family: "Microsoft YaHei"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 23
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop { position: 0.0; color: backButton.pressed ? Qt.darker("#3D3D3D", 1.1) : "#3D3D3D" }
                            GradientStop { position: 1.0; color: backButton.pressed ? Qt.darker("#2A2A2A", 1.1) : "#2A2A2A" }
                        }
                        border.width: 1
                        border.color: "#555555"

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: "#000000"
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 3
                            shadowBlur: 10
                            shadowOpacity: 0.3
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            backButton.clicked()
                        }
                        onEntered: backButton.scale = 1.05
                        onExited: backButton.scale = 1.0
                    }

                    Behavior on scale {
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.OutQuad
                        }
                    }

                    onClicked: {
                        event.updateState()
                        stack.pop()
                    }
                }

                Button {
                    id: startButton
                    text: "Start Game"
                    enabled: (!gameStarted || gameEnded) && betAmount > 0
                    width: 120
                    height: 46
                    visible: !gameStarted

                    contentItem: Text {
                        text: startButton.text
                        color: startButton.enabled ? "#ffffff" : "#9e9e9e"
                        font.pixelSize: 16
                        font.bold: true
                        font.family: "Microsoft YaHei"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 23
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop {
                                position: 0.0;
                                color: startButton.enabled ?
                                    (startButton.pressed ? Qt.darker(primaryColor, 1.1) : primaryColor) :
                                    "#333333"
                            }
                            GradientStop {
                                position: 1.0;
                                color: startButton.enabled ?
                                    (startButton.pressed ? Qt.darker(secondaryColor, 1.1) : secondaryColor) :
                                    "#444444"
                            }
                        }

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: startButton.enabled ? Qt.alpha(primaryColor, 0.5) : "#000000"
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 3
                            shadowBlur: 10
                            shadowOpacity: 0.3
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        enabled: startButton.enabled
                        onClicked: startButton.clicked()
                        onEntered: if (startButton.enabled) startButton.scale = 1.05
                        onExited: startButton.scale = 1.0
                    }

                    Behavior on scale {
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.OutQuad
                        }
                    }

                    onClicked: {
                        if (!gameStarted || gameEnded) {
                            guessType = gameClass.startGame(betAmount) + 1
                            gameStarted = true;
                            gameEnded = false
                        }
                    }
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30
                visible: gameStarted && !gameEnded

                Button {
                    id: guessFirstButton
                    text: guessType === 1 ? "Inside" : "Smaller"
                    width: 120
                    height: 46

                    contentItem: Text {
                        text: guessFirstButton.text
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.bold: true
                        font.family: "Microsoft YaHei"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 23
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop {
                                position: 0.0;
                                color: startButton.enabled ?
                                    (startButton.pressed ? Qt.darker(primaryColor, 1.1) : primaryColor) :
                                    "#333333"
                            }
                            GradientStop {
                                position: 1.0;
                                color: startButton.enabled ?
                                    (startButton.pressed ? Qt.darker(secondaryColor, 1.1) : secondaryColor) :
                                    "#444444"
                            }
                        }

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: startButton.enabled ? Qt.alpha(primaryColor, 0.5) : "#000000"
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 3
                            shadowBlur: 10
                            shadowOpacity: 0.3
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        enabled: guessFirstButton.enabled
                        onClicked: guessFirstButton.clicked()
                        onEntered: if (guessFirstButton.enabled) guessFirstButton.scale = 1.05
                        onExited: guessFirstButton.scale = 1.0
                    }

                    Behavior on scale {
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.OutQuad
                        }
                    }

                    onClicked: {
                        result = gameClass.makeGuess(0) + 1;
                        gameEnded = true;
                    }
                }

                Button {
                    id: guessSecondButton
                    text: guessType === 1 ? "Outside" : "Larger"
                    width: 120
                    height: 46

                    contentItem: Text {
                        text: guessSecondButton.text
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.bold: true
                        font.family: "Microsoft YaHei"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 23
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop {
                                position: 0.0;
                                color: startButton.enabled ?
                                    (startButton.pressed ? Qt.darker(primaryColor, 1.1) : primaryColor) :
                                    "#333333"
                            }
                            GradientStop {
                                position: 1.0;
                                color: startButton.enabled ?
                                    (startButton.pressed ? Qt.darker(secondaryColor, 1.1) : secondaryColor) :
                                    "#444444"
                            }
                        }

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: startButton.enabled ? Qt.alpha(primaryColor, 0.5) : "#000000"
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 3
                            shadowBlur: 10
                            shadowOpacity: 0.3
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        enabled: guessSecondButton.enabled
                        onClicked: guessSecondButton.clicked()
                        onEntered: if (guessSecondButton.enabled) guessSecondButton.scale = 1.05
                        onExited: guessSecondButton.scale = 1.0
                    }

                    Behavior on scale {
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.OutQuad
                        }
                    }

                    onClicked: {
                        result =  gameClass.makeGuess(1) + 1;
                        gameEnded = true;
                    }
                }
            }

            Rectangle {
                id: instructionBg
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 20
                width: instructionText.width + 40
                height: 36
                radius: 18
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: Qt.alpha(primaryColor, 0.1) }
                    GradientStop { position: 1.0; color: Qt.alpha(secondaryColor, 0.1) }
                }
                border.width: 1
                border.color: Qt.alpha(secondaryColor, 0.2)

                Text {
                    id: instructionText
                    anchors.centerIn: parent
                    color: secondaryColor
                    font.pixelSize: 14
                    font.family: "Microsoft YaHei"
                    text: result === 1 ? "Sorry, you lost!" :
                            result === 2 ? "Congratulations, you won!" : result === 3 ? "Hit the post！" : "Set your bet and start the game"
                }
            }
        }
    }
}
