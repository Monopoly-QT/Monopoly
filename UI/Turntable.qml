import QtQuick
import QtQuick.Shapes

Window{
    width: 700
    height: 700
    visible: true
    Item {
        id: root
        anchors.centerIn:parent
        property int rot: 0
        property bool animationEnable: true

        // 個數
        property int count: 5
        // 前count個扇型的顏色 （其餘的Random）
        property var colors:[ '#3D642D', '#F39F18', '#464531', '#84C3BE' , '#BDECB6']
        // 轉盤
        Item {
            id: item
            // 轉盤的大小
            width: 200
            height: item.width
            rotation: root.rot
            anchors.centerIn: parent
            Repeater {
                id: repeater
                model: root.count
                delegate: Shape {
                    ShapePath {
                        fillColor: root.colors[index] ?? "#" + Math.floor(Math.random() * 16777215).toString(16)
                        strokeColor: fillColor
                        capStyle: ShapePath.FlatCap
                        PathAngleArc {
                            centerX: item.width / 2
                            centerY: item.width / 2
                            radiusX: item.width; radiusY: item.width
                            startAngle: -(360 / repeater.model) * index
                            sweepAngle: -(360 / repeater.model)
                        }

                        PathLine {
                            x: item.width / 2
                            y: item.width / 2
                        }
                    }
                    Text {
                        text: (index+1)+" 天"
                        font.pixelSize: 20 * (100 - root.count) / 100
                        // 計算每個區塊的中心角度
                        property real angle: -(360 / root.count) * (index + 0.5)
                        // 半徑（可依需求調整）
                        property real r: item.width / 2 * 1.7
                        // 以圓心為基準，計算 x, y
                        x: item.width / 2 + r * Math.cos(angle * Math.PI / 180) - width / 2
                        y: item.width / 2 + r * Math.sin(angle * Math.PI / 180) - height / 2
                    }
                }
            }
            Behavior on rotation {
                enabled: root.animationEnable
                NumberAnimation {
                    duration: 8000
                    easing.type: Easing.InOutExpo
                    onRunningChanged: {
                        if (!running) {
                            root.rot %= 360;
                            root.animationEnable = true;
                            var a = 0;
                            for (let i = 0; i <= 360; i += 360 / root.count) {
                                if (root.rot % 360 <= i) {
                                    console.log(a);
                                    break;
                                }
                                a++;
                            }
                        } else {
                            root.animationEnable = false;
                        }
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    if (root.animationEnable) {
                        root.rot += Math.random() * 360 + 5400;
                    }
                }
            }
        }
        // 指針
        Canvas {
            x: item.x + item.width / 2 * 3
            y: item.y + item.height / 2 - height / 2
            // 指針大小
            width: 20
            height: width

            onPaint: {
                const ctx = getContext("2d");
                ctx.fillStyle = "black";
                ctx.moveTo(width, 0);
                ctx.lineTo(0, height / 2);
                ctx.lineTo(width, height);
                ctx.lineTo(width, 0);
                ctx.fill();
            }
        }
    }
}