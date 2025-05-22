#include "eventHandler.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include <QString>
#include <fstream>
#include <sstream>
#include <string>
#include "../Hospital/Hospital.h"

#include "Handler/MapHandler/mapHandler.h"
#include "ItemCard/DiceControl/DiceControlCard.h"

eventHandler::eventHandler(){
    turn = 0;

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

    nlohmann::json playerData;
    ifstream player;
    player.open("json/config.json");

    if (player.fail()) {
        cout << "Falied to open config.json\n";
    }

    player >> playerData;
    player.close();

    for(int i = 0 ; i < 4 ; i++){
        vector<int> ownCardFromConfig;
        string strOwnCardFromConfig = playerData[to_string(i)]["ownCard"].get<string>();
        stringstream ss(strOwnCardFromConfig);
        while(ss >> strOwnCardFromConfig){
            ownCardFromConfig.push_back(stoi(strOwnCardFromConfig));
        }
        Player* regis = new Player(playerData[to_string(i)]["money"].get<int>(),playerData[to_string(i)]["playerID"].get<int>(),playerData[to_string(i)]["playerName"].get<string>(),playerData[to_string(i)]["playerLastName"].get<string>(),ownCardFromConfig,playerData[to_string(i)]["pos"].get<int>(),playerData[to_string(i)]["state"].get<int>(),playerData[to_string(i)]["stayInHospitalTurn"].get<int>(),playerData[to_string(i)]["nextRollDicePoint"].get<int>());
        processPlayer.push_back(regis);
    }

    mapInitialize(landCoordinate,m_mapList,processMap,processPlayer);
    m_movePoint = &operateMovePoint;
    m_displayState = new StateDisplay();
    m_useCard = new UseCardSetting();

    processMap[13]->setOwner(1);
    processMap[13]->setLevel(4);
    mapUpdate(landCoordinate,m_mapList,processMap,processPlayer);

    for(int i=0;i<5;i++){
        processPlayer[0]->addOwnCards(i);
    }

    m_displayState -> initialStateDisplay(turn,processPlayer[turn]);
    m_useCard -> initialUseCardPopUp(turn,processMap,processPlayer);
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

void eventHandler::rocketCardUseEntryPoint(int _playerIndex, int _duration) {
    if (_duration <= 0) return;
    Player *player = processPlayer[_playerIndex];
    Hospital::enterHospital(player, _duration);
    cout << player->getPlayerName() << " is sent to the hospital for " << _duration << " rounds." << endl;
    processPlayer[turn]->disOwnCards(2);
    m_useCard -> initialUseCardPopUp(turn,processMap,processPlayer);
}

void eventHandler::diceCardUseEntryPoint(int _moveDistance){
    //TODO add function
    processPlayer[turn]->disOwnCards(0);
    m_useCard -> initialUseCardPopUp(turn,processMap,processPlayer);
}

void eventHandler::removeCardUseEntryPoint(QString _removeQStr){
    string regisStr = _removeQStr.toStdString();
    int location = 0;
    for(int i = 0 ; i < 64 ; i++){
        if(processMap[i]->getName() == regisStr){
            location = i;
            break;
        }
    }
    processMap[location]->setLevel(0);
    mapUpdate(landCoordinate,m_mapList,processMap,processPlayer);
    processPlayer[turn]->disOwnCards(3);
    m_useCard -> initialUseCardPopUp(turn,processMap,processPlayer);
}

void eventHandler::roadBlockCardUseEnrtyPoint(QString _blockQStr){
    string regisStr = _blockQStr.toStdString();
    regisStr = regisStr.substr(0,regisStr.find("."));
    int location = stoi(regisStr);
    processMap[location]->setState(1);
    processPlayer[turn]->disOwnCards(1);
    m_useCard -> initialUseCardPopUp(turn,processMap,processPlayer);
}

void eventHandler::eventCardUseEntryPoint(){
    //TODO add function
    processPlayer[turn]->disOwnCards(4);
    m_useCard -> initialUseCardPopUp(turn,processMap,processPlayer);
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


StateDisplay *eventHandler::displayState() const
{
    return m_displayState;
}

void eventHandler::setDisplayState(StateDisplay *newDisplayState)
{
    if (m_displayState == newDisplayState)
        return;
    m_displayState = newDisplayState;
    emit displayStateChanged();
}

UseCardSetting *eventHandler::useCard() const
{
    return m_useCard;
}

void eventHandler::setUseCard(UseCardSetting *newUseCard)
{
    if (m_useCard == newUseCard)
        return;
    m_useCard = newUseCard;
    emit useCardChanged();
}
