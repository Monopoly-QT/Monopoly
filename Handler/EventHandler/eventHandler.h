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

using namespace std;

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class eventHandler:public QObject{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> mapList READ mapList WRITE setMapList NOTIFY mapListChanged FINAL);
    Q_PROPERTY(MovePoint* movePoint READ movePoint WRITE setMovePoint NOTIFY movePointChanged FINAL);
    Q_PROPERTY(StateDisplay* displayState READ displayState WRITE setDisplayState NOTIFY displayStateChanged FINAL);
    Q_PROPERTY(UseCardSetting* useCard READ useCard WRITE setUseCard NOTIFY useCardChanged FINAL);
	Q_PROPERTY(int money READ showMoney NOTIFY moneyChanged);
    Q_PROPERTY(bool enableButton READ returnEnableButton NOTIFY EnableChanged);
public:
    eventHandler();
    ~eventHandler();

    Q_INVOKABLE void movePointAnimator(int _step);
    void animationThread(int _times,int _playerPos,int _index);

    QList<QObject *> mapList() const;
    void setMapList(const QList<QObject *> &newMapList);

    MovePoint *movePoint() const;
    void setMovePoint(MovePoint *newMovePoint);

    int nextLandIndex() const;
    void setNextLandIndex(int newNextLandIndex);

    Q_INVOKABLE void addMapPosXandPosY(double _posX, double _posY);
    Q_INVOKABLE void clearMapPosXandPosY();

    Q_INVOKABLE void moveEntryPoint(int _moveDistance);
    Q_INVOKABLE void commendEntryPoint(QString _instruct);

    int showMoney() const;
    bool returnEnableButton() const;
    void toll();
    Q_INVOKABLE void buyLand();
    Q_INVOKABLE void levelup();
    Q_INVOKABLE void sellLand();
    Q_INVOKABLE void rocketCardUseEntryPoint(int _playerIndex,int _duration);
    Q_INVOKABLE void diceCardUseEntryPoint(int _moveDistance);
    Q_INVOKABLE void removeCardUseEntryPoint(QString _removeQStr);
    Q_INVOKABLE void roadBlockCardUseEnrtyPoint(QString _blockQStr);
    Q_INVOKABLE void eventCardUseEntryPoint();


    StateDisplay *displayState() const;
    void setDisplayState(StateDisplay *newDisplayState);

    UseCardSetting *useCard() const;
    void setUseCard(UseCardSetting *newUseCard);

signals:
    void mapListChanged();
    void movePointChanged();
    void movePointStartMove();
    void movePointInitialize();
    void displayStateChanged();
    void useCardChanged();
    void moneyChanged();
    void EnableChanged();

private:
    int turn;
    bool buttonState = true;
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
};

#endif // EVENTHANDLER_H
