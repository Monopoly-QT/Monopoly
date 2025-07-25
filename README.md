# 大富翁 Monopoly
組別：Group 10

組員：B11315038 張智華、B11330046 王瑋琮、B11315022 黃楷駿、B11315040 許鑫勝

[Document]([https://hackmd.io/vbxi2d15TPaeFxqDpaYXjw](https://hackmd.io/@dafuwong/By56NL4Mel))

[Demo](https://youtu.be/YnqnBqD97M4)

## 程式架構
```
.
├── CMakeLists.txt
├── Dice
│   ├── Dice.cpp
│   └── Dice.h
├── Handler
│   ├── EventHandler
│   │   ├── eventHandler.cpp
│   │   ├── eventHandler.h
│   │   └── eventHandlerGetterSetter.cpp
│   └── MapHandler
│       ├── mapHandler.cpp
│       └── mapHandler.h
├── Hospital
│   ├── Hospital.cpp
│   └── Hospital.h
├── ItemCard
│   ├── Base
│   │   ├── ItemCard.cpp
│   │   └── ItemCard.h
│   ├── RoadblockCard
│   │   └── RoadblockCard.h
│   └── RocketCard
│       └── RocketCard.h
├── Land
│   ├── Land.cpp
│   └── Land.h
├── Map
│   ├── map.cpp
│   └── map.h
├── MiniGames
│   ├── DragonGate
│   │   ├── DragonGate.cpp
│   │   └── DragonGate.h
│   └── HorseRacing
│       ├── HorseRacing.cpp
│       └── HorseRacing.h
├── MovePoint
│   ├── MovePoint.cpp
│   └── MovePoint.h
├── Player
│   ├── Player.cpp
│   └── Player.h
├── Resources
│   ├── images
│   │   ├── Chang.png
│   │   ├── Chiang.png
│   │   ├── Horses
│   │   │   ├── horse1.png
│   │   │   ├── horse2.png
│   │   │   ├── horse3.png
│   │   │   └── horse4.png
│   │   ├── Tuan.png
│   │   ├── Wu.png
│   │   ├── building.png
│   │   ├── card.png
│   │   ├── cheat.png
│   │   ├── cheat_1.png
│   │   ├── grass_real.jpg
│   │   ├── house.png
│   │   ├── money.png
│   │   ├── roadBlock.png
│   │   └── shop
│   │       ├── background.png
│   │       ├── index0.png
│   │       ├── index1.png
│   │       ├── index2.png
│   │       ├── index3.png
│   │       └── index4.png
│   ├── json
│   │   ├── card.json
│   │   ├── command.json
│   │   ├── config.json
│   │   ├── country.json
│   │   └── event.json
│   └── resourse.qrc
├── Shop
│   ├── shop.cpp
│   └── shop.h
├── StateDisplay
│   ├── StateDisplay.cpp
│   └── StateDisplay.h
├── UI
│   ├── Bankruptcy_popUp.qml
│   ├── BuyLand_popUp.qml
│   ├── CardOpenBtn.qml
│   ├── CardPopup.qml
│   ├── CheatCommandLine.qml
│   ├── CheatCommandOpenBtn.qml
│   ├── Dice.qml
│   ├── DragonGate.qml
│   ├── EndPopUp.qml
│   ├── HorseRacing.qml
│   ├── Hospital_popup.qml
│   ├── Main.qml
│   ├── Message_popUp.qml
│   ├── RefreshPopup.qml
│   ├── ShopPopup.qml
│   ├── StateContainer.qml
│   ├── Turntable.qml
│   ├── UpgradeOrSell_popUp.qml
│   └── baseWidget
│       ├── CostumBtn_Rec.qml
│       └── Standard_Text.qml
├── UseCardSetting
│   ├── UseCardSetting.cpp
│   └── UseCardSetting.h
├── include
│   └── nlohmann
│       └── json.hpp
├── README.md
└── main.cpp

```

## 程式碼編譯方式

1. 使用學校email信箱到Qt官網申請Qt教育版憑證帳號（Qt Educational License）https://www.qt.io/qt-educational-license#application。

2. 72小時內至學校信箱收取Qt Company官方寄來的確認信，主旨為：Your Qt Educational license is on its way! Verify your email.。

3. 確認信會自動導向下載網址，下載安裝檔（online installer）

4. 執行安裝檔（online installer），登入申請的Qt教育版帳號，點選「Next」。

5. 進入歡迎安裝介面，點選「Next」。

6. 將「用於桌面開發的Qt 6.9（Qt 6.9 for desktop development）」打勾，點選「Next」。

7. 閱讀相關憑證協定，底下選項全勾，之後一直點「Next」進行安裝。

8. 安裝完成後，啟動Qt Creator。

9. 點選Open Project，瀏覽資料夾，點選Project資料夾中的CmakeLists.txt，按「開啟」。

10. 如果出現「No valid Settings Found」，點選「確定」。

11. 把「Select all kits打勾」，點選「Configure Project」。

12. 等它跑完後，按下左下角倒數第三個的「執行」，或是按快捷鍵「Ctrl+R」。

13. 程式編譯執行成功！
