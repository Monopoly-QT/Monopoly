import QtQuick
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Basic
import QtQuick.Effects
import "../../"

Page {
    id: horseRacingRoot
    visible: true

    property color primaryColor: "#FF5252"        // 鮮豔的紅色作為主色調
    property color secondaryColor: "#FFAB40"      // 橙色作為輔助色
    property color accentColor: "#40C4FF"         // 亮藍色作為強調色

    property int betAmount: 100
    property bool gameStarted: false
    property int betHorse: 0
    property int playerTurn: 0

    Connections {
        target: gameClass
        onUpdateState: {
            event.updateState();
        }
    }

    Connections {
        target: event
        onCloseAllPopups: {
            stack.pop();
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: Qt.darker("#121212", 1.2)
            }
            GradientStop {
                position: 1.0
                color: "#121212"
            }
        }
    }

    Canvas {
        width: parent.width
        height: parent.height
        onPaint: {
            horseRacingRoot.playerTurn = event.getTurn();
            var ctx = getContext("2d");
            ctx.lineWidth = 1;
            ctx.strokeStyle = Qt.rgba(1, 1, 1, 0.03);
            for (let i = 0; i < width; i += 30) {
                ctx.beginPath();
                ctx.moveTo(i, 0);
                ctx.lineTo(i, height);
                ctx.stroke();
            }

            for (i = 0; i < height; i += 30) {
                ctx.beginPath();
                ctx.moveTo(0, i);
                ctx.lineTo(width, i);
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
            GradientStop {
                position: 0.0; color: primaryColor
            }
            GradientStop {
                position: 0.5; color: secondaryColor
            }
            GradientStop {
                position: 1.0; color: accentColor
            }
        }
        anchors.top: parent.top
    }

    Column {
        width: parent.width
        height: parent.height
        topPadding: 30
        spacing: 20

        // 標題列
        Item {
            height: title.height
            width: parent.width
            Text {
                id: title
                text: "Horse Racing"
                color: "#ffffff"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 46
            }

            Rectangle {
                id: moneyDisplay
                width: 180
                height: 40
                radius: 20
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop {
                        position: 0.0; color: Qt.alpha(primaryColor, 0.1)
                    }
                    GradientStop {
                        position: 1.0; color: Qt.alpha(secondaryColor, 0.15)
                    }
                }
                border.width: 1
                border.color: Qt.alpha(secondaryColor, 0.3)
                anchors.right: parent.right
                anchors.rightMargin: 20
                Row {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 8
                    Rectangle {
                        border.width: 2
                        border.color: secondaryColor
                        width: 24
                        height: 24
                        radius: 360
                        anchors.verticalCenter: parent.verticalCenter
                        color: Qt.alpha(secondaryColor, 0.2)
                        Text {
                            text: "$"
                            color: secondaryColor
                            anchors.centerIn: parent
                            font.pixelSize: 14
                            font.bold: true
                        }
                    }

                    Text {
                        text: "Balance: "
                        color: "#ffffff"
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 14
                        font.bold: true
                    }
                }

                Text {
                    text: playerClass.money
                    color: secondaryColor
                    font.pixelSize: 15
                    font.bold: true
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 10
                }
            }
        }

        // 草地
        Rectangle {
            id: container
            width: parent.width * 0.9
            height: parent.height * 0.55
            color: Qt.rgba(0, 0, 0, 0.2)
            radius: 15
            anchors.horizontalCenter: parent.horizontalCenter
            Image {
                width: parent.width
                height: parent.height
                source: "qrc:/images/grass_real.jpg"
            }

            Rectangle {
                width: 7
                height: parent.height
                color: "black"
                x: parent.width - horse1.width - width - 2
            }

            Rectangle {
                width: 7
                height: parent.height
                color: "black"
                x: horse1.width + width + 2

            }

            // 馬匹編號
            Column {
                height: parent.height
                x: parent.width - horse1.width

                property int textHeight: height / 4 * 0.8

                Repeater {
                    model: 4
                    delegate: Item {
                        width: parent.width - (parent.width - horse1.width)
                        height: parent.height / 4

                        Text {
                            text: index + 1
                            font.pixelSize: parent.parent.textHeight
                            anchors.centerIn: parent
                            color: "#000000"
                            opacity: 0.6
                            font.bold: true
                        }
                    }
                }
            }

            // 四隻馬
            Column {
                width: parent.width
                height: parent.height
                Rectangle {
                    width: parent.width
                    height: parent.height / 4
                    color: Qt.alpha("#21410e", 0.6)
                    Image {
                        id: horse1
                        height: parent.height * 0.8
                        source: "qrc:/images/Horses/horse1.png"
                        opacity: 1
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        x: (parent.width - width) *
                            (((gameClass.horsesPrecess[0] ?? 0) / 100) > 100 ? 100 :
                                ((gameClass.horsesPrecess[0] ?? 0) / 100))

                        Behavior on x {
                            NumberAnimation {
                                duration: 500
                                easing.type: Easing.Linear
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 4
                    color: Qt.alpha("#466a23", 0.6)
                    Image {
                        id: horse2
                        height: parent.height * 0.8
                        source: "qrc:/images/Horses/horse2.png"
                        opacity: 1
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        x: (parent.width - width) *
                            (((gameClass.horsesPrecess[1] ?? 0) / 100) > 100 ? 100 :
                                ((gameClass.horsesPrecess[1] ?? 0) / 100))

                        Behavior on x {
                            NumberAnimation {
                                duration: 500
                                easing.type: Easing.Linear
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 4
                    color: Qt.alpha("#21410e", 0.6)
                    Image {
                        id: horse3
                        height: parent.height * 0.8
                        source: "qrc:/images/Horses/horse3.png"
                        opacity: 1
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        x: (parent.width - width) *
                            (((gameClass.horsesPrecess[2] ?? 0) / 100) > 100 ? 100 :
                                ((gameClass.horsesPrecess[2] ?? 0) / 100))

                        Behavior on x {
                            NumberAnimation {
                                duration: 500
                                easing.type: Easing.Linear
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 4
                    color: Qt.alpha("#466a23", 0.6)
                    Image {
                        id: horse4
                        height: parent.height * 0.8
                        source: "qrc:/images/Horses/horse4.png"
                        opacity: 1
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        x: (parent.width - width) *
                            (((gameClass.horsesPrecess[3] ?? 0) / 100) > 100 ? 100 :
                                ((gameClass.horsesPrecess[3] ?? 0) / 100))

                        Behavior on x {
                            NumberAnimation {
                                duration: 500
                                easing.type: Easing.Linear
                            }
                        }
                    }
                }
            }

            // 啟用圖層 （允許內容被渲染到單一換衝區）
            layer.enabled: true
            // 遮罩效果
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: container.width
                    height: container.height
                    radius: container.radius
                }
            }
        }

        // Spin Box
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            width: children[0].width * 2 + 10
            height: children[0].height
            spacing: 10

            // 金額調整
            SpinBox {
                id: betSpinBox
                from: 0
                to: playerClass.money
                stepSize: 100
                width: parent.parent.width * 0.3
                height: 40
                value: horseRacingRoot.betAmount
                enabled: !gameStarted

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
                        GradientStop {
                            position: 0.0; color: "#2A2A2A"
                        }
                        GradientStop {
                            position: 1.0; color: "#3D3D3D"
                        }
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

                up.indicator: Rectangle {
                    x: betSpinBox.mirrored ? 0 : parent.width - width
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop {
                            position: 0.0; color: Qt.alpha(primaryColor, 0.1)
                        }
                        GradientStop {
                            position: 1.0; color: Qt.alpha(secondaryColor, 0.15)
                        }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)

                    Text {
                        text: "+"
                        font.pixelSize: betSpinBox.font.pixelSize * 1.5
                        color: "#ffffff"
                        font.bold: true
                        anchors.fill: parent
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                down.indicator: Rectangle {
                    x: 0
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop {
                            position: 0.0; color: Qt.alpha(primaryColor, 0.1)
                        }
                        GradientStop {
                            position: 1.0; color: Qt.alpha(secondaryColor, 0.15)
                        }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)

                    Text {
                        text: "-"
                        font.pixelSize: betSpinBox.font.pixelSize * 1.5
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

            // 馬調整
            SpinBox {
                id: betHorseSpinBox
                from: 1
                to: 4
                stepSize: 1
                width: parent.parent.width * 0.3
                height: 40
                value: horseRacingRoot.betHorse
                enabled: !gameStarted

                onValueChanged: {
                    horseRacingRoot.betHorse = value
                }

                contentItem: Text {
                    text: "Horse " + horseRacingRoot.betHorse
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
                        GradientStop {
                            position: 0.0; color: "#2A2A2A"
                        }
                        GradientStop {
                            position: 1.0; color: "#3D3D3D"
                        }
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

                up.indicator: Rectangle {
                    x: betSpinBox.mirrored ? 0 : parent.width - width
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop {
                            position: 0.0; color: Qt.alpha(primaryColor, 0.1)
                        }
                        GradientStop {
                            position: 1.0; color: Qt.alpha(secondaryColor, 0.15)
                        }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)

                    Text {
                        text: "+"
                        font.pixelSize: betSpinBox.font.pixelSize * 1.5
                        color: "#ffffff"
                        font.bold: true
                        anchors.fill: parent
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                down.indicator: Rectangle {
                    x: 0
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop {
                            position: 0.0; color: Qt.alpha(primaryColor, 0.1)
                        }
                        GradientStop {
                            position: 1.0; color: Qt.alpha(secondaryColor, 0.15)
                        }
                    }
                    border.width: 1
                    border.color: Qt.alpha(secondaryColor, 0.3)

                    Text {
                        text: "-"
                        font.pixelSize: betSpinBox.font.pixelSize * 1.5
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
        }

        // 按鈕
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button {
                id: backButton
                text: "Back"
                width: 120
                height: 46
                visible: gameClass.winner != -1 || playerClass.money <= 0

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
                        GradientStop {
                            position: 0.0; color: backButton.pressed ? Qt.darker("#3D3D3D", 1.1) : "#3D3D3D"
                        }
                        GradientStop {
                            position: 1.0; color: backButton.pressed ? Qt.darker("#2A2A2A", 1.1) : "#2A2A2A"
                        }
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
                    onClicked: backButton.clicked()
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
                    if (horseRacingRoot.playerTurn === event.getTurn()) {
                        event.nextTurn();
                    }
                    stack.pop()
                }
            }
            Button {
                id: startButton
                text: "Start Game"
                width: 120
                height: 46
                enabled: !horseRacingRoot.gameStarted && horseRacingRoot.betAmount > 0 && playerClass.money > 0
                visible: gameClass.winner == -1

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
                    gameClass.mainGame(betAmount, betHorse - 1);
                    horseRacingRoot.gameStarted = true
                }
            }
        }

        // 提示文字
        Rectangle {
            id: instructionBg
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20
            width: instructionText.width + 40
            height: 36
            radius: 18
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop {
                    position: 0.0; color: Qt.alpha(primaryColor, 0.1)
                }
                GradientStop {
                    position: 1.0; color: Qt.alpha(secondaryColor, 0.1)
                }
            }
            border.width: 1
            border.color: Qt.alpha(secondaryColor, 0.2)

            Text {
                id: instructionText
                anchors.centerIn: parent
                color: secondaryColor
                font.pixelSize: 14
                font.family: "Microsoft YaHei"
                text: gameClass.winner === -1 ? "Set your bet and start the game" :
                        gameClass.winner !== (horseRacingRoot.betHorse - 1) ? "Sorry, you lost! The winner is Horse " + (gameClass.winner + 1)
                        : "Congratulations, you won!"
            }
        }

    }
}
