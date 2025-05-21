import QtQuick
import QtQuick.Shapes

Item {
    id: turntableRoot
    property int rot: 0
    property bool animationEnable: true

    // 個數
    property int count: 5
    // 前count個扇型的顏色 （其餘的Random）
    property var colors:[ '#3D642D', '#F39F18', '#464531', '#84C3BE' , '#BDECB6']
    property var afterRotate: {}
    property int rotatedIndex: 0

    // 轉盤
    Item {
        id: turntable
        // 轉盤的大小
        width: parent.width
        height: turntable.width
        rotation: turntableRoot.rot
        Repeater {
            id: repeater
            model: turntableRoot.count
            delegate: Shape {
                ShapePath {
                    fillColor: turntableRoot.colors[index] ?? "#" + Math.floor(Math.random() * 16777215).toString(16)
                    strokeColor: fillColor
                    capStyle: ShapePath.FlatCap
                    PathAngleArc {
                        centerX: turntable.width / 2
                        centerY: turntable.width / 2
                        radiusX: turntable.width; radiusY: turntable.width
                        startAngle: -(360 / repeater.model) * index
                        sweepAngle: -(360 / repeater.model)
                    }

                    PathLine {
                        x: turntable.width / 2
                        y: turntable.width / 2
                    }
                }
                Text {
                    text: (index+1)+" Days"
                    font.pixelSize: 20 * (100 - turntableRoot.count) / 100
                    // 計算每個區塊的中心角度
                    property real angle: -(360 / turntableRoot.count) * (index + 0.5)
                    // 半徑（可依需求調整）
                    property real r: turntable.width / 2 * 1.3
                    // 以圓心為基準，計算 x, y
                    x: turntable.width / 2 + r * Math.cos(angle * Math.PI / 180) - width / 2
                    y: turntable.width / 2 + r * Math.sin(angle * Math.PI / 180) - height / 2
                }
            }
        }
        Behavior on rotation {
            enabled: turntableRoot.animationEnable
            NumberAnimation {
                duration: 3000
                easing.type: Easing.InOutExpo
                onRunningChanged: {
                    if (!running) {
                        turntableRoot.rot %= 360;
                        turntableRoot.animationEnable = true;
                        var a = 0;
                        for (let i = 0; i <= 360; i += 360 / turntableRoot.count) {
                            if (turntableRoot.rot % 360 <= i) {
                                turntableRoot.rotatedIndex = a;
                                if (turntableRoot.afterRotate && typeof turntableRoot.afterRotate === "function") {
                                    turntableRoot.afterRotate();
                                }
                                break;
                            }
                            a++;
                        }
                    } else {
                        turntableRoot.animationEnable = false;
                    }
                }
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked:{

            }
        }
    }
    // 指針
    Canvas {
        x: turntable.x + turntable.width / 2 * 3 + 3
        y: turntable.y + turntable.height / 2 - height / 2
        // 指針大小
        width: 10
        height: width

        onPaint: {
            const ctx = getContext("2d");
            ctx.fillStyle = "white";
            ctx.moveTo(width, 0);
            ctx.lineTo(0, height / 2);
            ctx.lineTo(width, height);
            ctx.lineTo(width, 0);
            ctx.fill();
        }
    }
}
