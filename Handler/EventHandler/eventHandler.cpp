#include "eventHandler.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include <QString>
#include <fstream>

#include "Handler/MapHandler/mapHandler.h"

eventHandler::eventHandler(){
    turn = 1;

    nlohmann::json countryData;
    ifstream country;
    country.open("json/country.json");

    if (country.fail()) {
        cout << "Falied to open country.json\n";
    }

    country >> countryData;
    country.close();

    for(int i = 0 ; i < 64 ; i++){
        Land* regis=new Land(countryData[to_string(i)]["type"].get<int>(), i, countryData[to_string(i)]["name"].get<string>(), countryData[to_string(i)]["value"].get<int>(), countryData[to_string(i)]["translation"].get<string>());
        regis->setLevel(0);
        processMap.push_back(regis);
    }
    for(int i = 0 ; i < 4 ; i++){
        Player* regis = new Player();
        regis->setPos(0);
        processPlayer.push_back(regis);
    }
    processMap[0]->setOwner(1);
    processMap[1]->setOwner(2);
    processMap[2]->setOwner(3);
    processMap[3]->setOwner(4);
    processMap[4]->setType(1);
    processMap[5]->setType(2);
    processMap[6]->setType(3);
    mapInitialize(landCoordinate,m_mapList,processMap,processPlayer);
    m_movePoint = &operateMovePoint;
}

eventHandler::~eventHandler(){
    for(auto i:processMap){
        delete i;
    }
    for(auto i:processPlayer){
        delete i;
    }
    processMap.clear();
    processPlayer.clear();
}

void eventHandler::moveEntryPoint(int _moveDistance){
    cout<<_moveDistance<<endl;
}

void eventHandler::commendEntryPoint(QString _instruct){
    string strInstruct =  _instruct.toStdString();

}

void eventHandler::addMapPosXandPosY(double _posX, double _posY){
    mapPosXandPosY.push_back({_posX,_posY});
}

void eventHandler::clearMapPosXandPosY(){
    mapPosXandPosY.clear();
}


void eventHandler::movePointAnimator(){
    int playerPos = processPlayer[0]->getPos();
    int index = landCoordinate[playerPos];
    if(processPlayer[0]->getPos() == 0){
        operateMovePoint.setChangeX(mapPosXandPosY[0].first);
        operateMovePoint.setChangeY(mapPosXandPosY[0].second);
    }
    double posX = mapPosXandPosY[index].first;
    double posY = mapPosXandPosY[index].second;
    operateMovePoint.initializeMovePoint(posX,posY,0);
    emit movePointInitialize();
    std::thread t(&eventHandler::animationThread,this,64,playerPos,index);
    t.detach();
}

void eventHandler::animationThread(int _times,int _playerPos,int _index){
    QMetaObject::invokeMethod(&operateMovePoint,"setIsvisable",Qt::QueuedConnection,Q_ARG(bool,true));
    for(int i=0;i<_times;i++){
        this_thread::sleep_for(chrono::milliseconds(350));
        if(processPlayer[0]->getPos() == 63){
            processPlayer[0]->setPos(0);
            _playerPos = processPlayer[0]->getPos();
            _index = landCoordinate[_playerPos];
        }
        else{
            _playerPos++;
            processPlayer[0]->setPos(_playerPos);
            _index = landCoordinate[_playerPos];
        }
        operateMovePoint.movingMovePoint(mapPosXandPosY[_index].first,mapPosXandPosY[_index].second);
        QMetaObject::invokeMethod(this, "movePointStartMove", Qt::QueuedConnection);
    }
    this_thread::sleep_for(chrono::milliseconds(250));
    QMetaObject::invokeMethod(&operateMovePoint, "hiddingMovePoint", Qt::QueuedConnection);
}


QList<QObject *> eventHandler::mapList() const
{
    return m_mapList;
}

void eventHandler::setMapList(const QList<QObject *> &newMapList)
{
    if (m_mapList == newMapList)
        return;
    m_mapList = newMapList;
    emit mapListChanged();
}



MovePoint *eventHandler::movePoint() const
{
    return m_movePoint;
}

void eventHandler::setMovePoint(MovePoint *newMovePoint)
{
    if (m_movePoint == newMovePoint)
        return;
    m_movePoint = newMovePoint;
    emit movePointChanged();
}

