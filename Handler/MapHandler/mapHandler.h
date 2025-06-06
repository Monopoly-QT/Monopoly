#include "../../Map/map.h"
#include "../../Land/Land.h"
#include "../../Player/Player.h"
#include <vector>
#include <QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include <QList>
#include <QString>

using namespace std;


#ifndef MAPHANDLER_H
#define MAPHANDLER_H

void mapInitialize(vector<int> &landCoordinate ,QList<QObject*> &m_mapList ,vector<Land*> land,vector<Player*> player);

void mapUpdate(vector<int> landCoordinate ,QList<QObject*> &m_mapList ,vector<Land*> land,vector<Player*> player);

void hideSpecificPLayer(vector<int> landCoordinate ,QList<QObject*> &m_mapList ,Player* player,int turn);


#endif // MAPHANDLER_H
