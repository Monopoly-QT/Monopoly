#include "../../Dice/Dice.h"
#include "../../Map/map.h"
#include "../../Land/Land.h"
#include "../../Player/Player.h"
#include "../../MovePoint/MovePoint.h"
#include "../../Handler/MapHandler/mapHandler.h"
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

public:
    eventHandler();
    ~eventHandler();
    Q_INVOKABLE void movePointAnimator();
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

    Q_INVOKABLE void rocketCardUseEntryPoint(int _playerIndex,int _duration);
    // Q_INVOKABLE void diceCardUseEntryPoint(int _moveDistance);
    // Q_INVOKABLE void removeCardUseEntryPoint(int _removeIndex);
    // Q_INVOKABLE void roadBlockCardUseEnrtyPoint(int _blockIndex);
    // Q_INVOKABLE void eventCardUseEntryPoint();

signals:
    void mapListChanged();
    void movePointChanged();
    void movePointStartMove();
    void movePointInitialize();

private:
    int turn;

    QList<QObject *> m_mapList;
    vector<int> landCoordinate;

    vector<Land*> processMap;
    vector<Player*> processPlayer;

    MovePoint *m_movePoint;
    MovePoint operateMovePoint;

    vector<pair<double,double>> mapPosXandPosY;
};

#endif // EVENTHANDLER_H
