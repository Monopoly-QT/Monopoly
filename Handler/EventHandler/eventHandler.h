#include "../../Dice/Dice.h"
#include "../../Map/map.h"
#include "../../Land/Land.h"
#include "../../Player/Player.h"
#include "../../MovePoint/MovePoint.h"
#include "../../Handler/MapHandler/mapHandler.h"
#include "../../UseCardSetting/UseCardSetting.h"
#include "../../StateDisplay/StateDisplay.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <QObject>
#include <QList>
#include <QString>
#include <QQmlApplicationEngine>

#include "MiniGames/DragonGate/DragonGate.h"
#include "MiniGames/HorseRacing/HorseRacing.h"

using namespace std;

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class eventHandler:public QObject{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> mapList READ mapList WRITE setMapList NOTIFY mapListChanged FINAL);
    Q_PROPERTY(MovePoint* movePoint READ movePoint WRITE setMovePoint NOTIFY movePointChanged FINAL);
    Q_PROPERTY(StateDisplay* displayState READ displayState WRITE setDisplayState NOTIFY displayStateChanged FINAL);
    Q_PROPERTY(UseCardSetting* useCard READ useCard WRITE setUseCard NOTIFY useCardChanged FINAL);
    Q_PROPERTY(QString displayMessage READ displayMessage WRITE setDisplayMessage NOTIFY displayMessageChanged FINAL);
    Q_PROPERTY(bool diceEnabled READ diceEnabled WRITE setDiceEnabled NOTIFY diceEnabledChanged FINAL);

public:
    eventHandler(QQmlApplicationEngine *engine);
    ~eventHandler();

    Q_INVOKABLE void movePointAnimator(int _step);
    void animationThread(int _times,int _playerPos,int _index);

    QList<QObject *> mapList() const;
    void setMapList(const QList<QObject *> &newMapList);

    MovePoint *movePoint() const;
    void setMovePoint(MovePoint *newMovePoint);

    int nextLandIndex() const;
    void setNextLandIndex(int newNextLandIndex);
    void toll();
    void popUpdisplaySetting(string _message,int _type); //set upgraade,buy,message popUp  Type: 0:message 1:buy 2:upgrade

    Q_INVOKABLE void afterMove();
    Q_INVOKABLE void addMapPosXandPosY(double _posX, double _posY);
    Q_INVOKABLE void clearMapPosXandPosY();
    Q_INVOKABLE void moveEntryPoint(int _moveDistance);
    Q_INVOKABLE void commendEntryPoint(QString _instruct);
    Q_INVOKABLE void buyLand();
    Q_INVOKABLE void levelup();
    Q_INVOKABLE void sellLand();
    Q_INVOKABLE void rocketCardUseEntryPoint(int _playerIndex,int _duration);
    Q_INVOKABLE void diceCardUseEntryPoint(int _moveDistance);
    Q_INVOKABLE void removeCardUseEntryPoint(QString _removeQStr);
    Q_INVOKABLE void sellLandFromStrUseEntryPoint(QString _removeQStr);

    Q_INVOKABLE void roadBlockCardUseEnrtyPoint(QString _blockQStr);
    Q_INVOKABLE void eventCardUseEntryPoint();
    Q_INVOKABLE bool buyItemEntryPoint(int price , int itemIndex);
    Q_INVOKABLE void nextTurn();
    Q_INVOKABLE void suicidal();
    Q_INVOKABLE void updateState();
    Q_INVOKABLE bool checkIsGameEnded();
    Q_INVOKABLE void restart(bool first);

    bool checkIsBankrupt();


    StateDisplay *displayState() const;
    void setDisplayState(StateDisplay *newDisplayState);

    UseCardSetting *useCard() const;
    void setUseCard(UseCardSetting *newUseCard);

    QString displayMessage() const;
    void setDisplayMessage(const QString &newDisplayMessage);

    bool diceEnabled() const;
    void setDiceEnabled(bool newDiceEnabled);

    void gameEnd();

signals:
    void mapListChanged();
    void movePointChanged();
    void movePointStartMove();
    void movePointInitialize();
    void displayStateChanged();
    void useCardChanged();
    void startRefresh();
    void openShopPopup();
    void displayMessageChanged();
    void openUpgradePopup(bool upgradeable,bool sellable);
    void openBuyPopup();
    void openMessage();
    void openBankruptcy();
    void gameStateInit();
    void gameStateStart();
    void gameStateMoved();
    void gameStateFinish();
    void diceEnabledChanged();
    void openDragonGate();
    void openHorseRacing();
    void openEndPopup();

private:
    int turn;
    bool firstClick = true;

    map<string, int> playerNameToID;

    QList<QObject *> m_mapList;
    vector<int> landCoordinate;

    vector<Land*> processMap;
    vector<Player*> processPlayer;

    MovePoint *m_movePoint;
    MovePoint operateMovePoint;

    vector<pair<double,double>> mapPosXandPosY;

    StateDisplay *m_displayState;
    UseCardSetting *m_useCard;
    QString m_displayMessage;

    QQmlApplicationEngine *engine;

    HorseRacing horseRacingGameObject;
    DragonGate dragonGateGameObject;

    bool m_diceEnabled = true;
    int m_endMoney = 0;
};

#endif // EVENTHANDLER_H
