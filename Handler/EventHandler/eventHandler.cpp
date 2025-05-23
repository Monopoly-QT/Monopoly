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
#include <regex>
#include <QQmlApplicationEngine>
#include "../Hospital/Hospital.h"

#include "Handler/MapHandler/mapHandler.h"
#include "ItemCard/DestroyImmovableCard/DestroyImmovableCard.h"
#include "ItemCard/DiceControl/DiceControlCard.h"
#include "ItemCard/RandomEventCard/RandomEventCard.h"
#include "ItemCard/RoadblockCard/RoadblockCard.h"
#include "ItemCard/RocketCard/RocketCard.h"
#include "Shop/shop.h"
// #include "MiniGames/DragonGate/DragonGate.h"

bool checkNum(string needChecked) {
    for (int i = 0; i < needChecked.size(); i++) {
        if (!isdigit(needChecked[i])) {
            return false;
        }
    }

    return true;
}

// void initialize();

// void start();

// void moved();

// void finish();

// void printAllPlayerInfo();

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
        // landNameToPos[regis->getName()] = i;
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

        playerNameToID[regis->getPlayerLastName()] = regis->getID();
    }

    mapInitialize(landCoordinate,m_mapList,processMap,processPlayer);
    m_movePoint = &operateMovePoint;
    m_displayState = new StateDisplay();
    m_useCard = new UseCardSetting();

    processMap[13]->setOwner(1);
    processMap[13]->setLevel(4);
    mapUpdate(landCoordinate,m_mapList,processMap,processPlayer);

    // for(int i=0;i<5;i++){
    //     processPlayer[0]->addOwnCards(i);
    // }

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

void eventHandler::moveEntryPoint(int _moveDistance) {
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    buttonState = true;
    emit EnableChanged();
    movePointAnimator(_moveDistance);
}

void eventHandler::commendEntryPoint(QString _instruct){
    string strInstruct =  _instruct.toStdString();

    nlohmann::json commandData;
    ifstream command;
    command.open("json/command.json");

    if (command.fail()) {
        cout << "Falied to open command.json\n";
    }

    command >> commandData;
    command.close();

    string inputCommand = strInstruct;
    string prompt;
    stringstream ss(inputCommand);

    while (ss >> inputCommand) {
        if (inputCommand == "/move") {
            prompt = commandData["move"]["prompt"].get<string>();
            regex r1(R"(\{playerName\})");
            prompt = regex_replace(prompt, r1, processPlayer[turn]->getPlayerName());
            ss >> inputCommand;
            if (checkNum(inputCommand)) {
                processPlayer[turn]->addPos(stoi(inputCommand));
                regex r(R"(\{location\})");
                prompt = regex_replace(prompt, r, to_string(processPlayer[turn]->getPos()));
                mapUpdate(landCoordinate,m_mapList,processMap,processPlayer);
                cout << prompt << '\n';
                popUpdisplaySetting(prompt, 0);
            }
            else if (inputCommand == "to") {
                ss >> inputCommand;
                if (checkNum(inputCommand) && stoi(inputCommand) <= 64) {
                    int newPos = stoi(inputCommand) % 64;
                    processPlayer[turn]->setPos(newPos);
                    regex r(R"(\{location\})");
                    prompt = regex_replace(prompt, r, to_string(newPos));
                    mapUpdate(landCoordinate,m_mapList,processMap,processPlayer);
                    cout << prompt << '\n';
                    popUpdisplaySetting(prompt, 0);
                }
                else {
                    cout << "Valid input!\n";
                    popUpdisplaySetting("Valid input!\n", 0);
                    break;
                }
            }
            else {
                cout << "Valid input!\n";
                popUpdisplaySetting("Valid input!\n", 0);
                break;
            }
        }
        else if (inputCommand == "/give") {
            prompt = commandData["give"]["prompt"].get<string>();

            string payee;
            ss >> payee;

            bool valid = 0;
            for (int i = 0; i < 4; i++) {
                if (payee == processPlayer[i]->getPlayerLastName()) {
                    valid = 1;
                    break;
                }
            }

            if (!valid) {
                cout << "Valid input!\n";
                popUpdisplaySetting("Valid input!\n", 0);
                break;
            }

            regex r1(R"(\{playerName\})");
            prompt = regex_replace(prompt, r1, payee);

            ss >> inputCommand;
            int deltaMoney = stoi(inputCommand);
            regex r2(R"(\{money\})");
            prompt = regex_replace(prompt, r2, to_string(deltaMoney));

            if (processPlayer[turn]->getMoney() < deltaMoney) {
                cout << "Error: " << processPlayer[turn]->getPlayerName() << "don't have enough money.\n";
                popUpdisplaySetting("Error: "+processPlayer[turn]->getPlayerName()+"don't have enough money.\n", 0);
                break;
            }

            processPlayer[turn]->subMoney(deltaMoney);
            processPlayer[playerNameToID[payee]]->addMoney(deltaMoney);
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            cout << prompt << '\n';
            popUpdisplaySetting(prompt, 0);

        }
        else if (inputCommand == "/get") {
            prompt = commandData["get"]["prompt"].get<string>();
            ss >> inputCommand;
            if (checkNum(inputCommand)) {
                int deltaMoney = stoi(inputCommand);
                regex r1(R"(\{playerName\})");
                prompt = regex_replace(prompt, r1, processPlayer[turn]->getPlayerName());
                regex r2(R"(\{money\})");
                prompt = regex_replace(prompt, r2, to_string(deltaMoney));
                processPlayer[turn]->addMoney(deltaMoney);
                m_displayState->initialStateDisplay(turn, processPlayer[turn]);
                cout << prompt << '\n';
                popUpdisplaySetting(prompt, 0);
            }
            else {
                cout << "Valid input!\n";
                popUpdisplaySetting("Valid input!\n", 0);
                break;
            }
        }
        // else if (inputCommand == "/card") {
        //     prompt = commandData["card"]["prompt"].get<string>();
        //     ss >> inputCommand;
        //     processPlayer[turn]->addOwnCards(inputCommand);
        //     regex r(R"(\{card_name\})");
        //     prompt = regex_replace(prompt, r, inputCommand);
        //     cout << prompt << '\n';
        // }
        else if (inputCommand == "/minigame") {
            prompt = commandData["minigame"]["prompt"].get<string>();
            cout << prompt << '\n';
            popUpdisplaySetting(prompt, 0);
            ss >> inputCommand;
            // DragonGate::init(processPlayer[turn]);
        }
        else if (inputCommand == "/gamestate") {
            prompt = commandData["gamestate"]["prompt"].get<string>();
            ss >> inputCommand;
            if (inputCommand == "INIT") {
                // initialize();
            }
            else if (inputCommand == "START") {
                // start();
            }
            else if (inputCommand == "MOVED") {
                // moved();
            }
            else if (inputCommand == "FINISH") {
                // finish();
            }
            regex r(R"(\{state\})");
            prompt = regex_replace(prompt, r, inputCommand);
            cout << prompt << '\n';
            popUpdisplaySetting(prompt, 0);
        }
        else if (inputCommand == "/info") {
            cout << commandData["info"]["prompt"].get<string>();
            // printAllPlayerInfo();
        }
        else if (inputCommand == "/refresh") {
            cout << commandData["refresh"]["prompt"].get<string>();
            emit startRefresh();
        }
        else if (inputCommand == "/list" || inputCommand == "/help") {
            string prompt;
            bool a = false;

            if (ss >> inputCommand) {
                if (inputCommand == "-a") {
                    a = true;
                }
            }

            for (auto x : commandData) {
                if (x["name"].get<string>() != "") {
                    cout << x["name"].get<string>() << " - " << x["description"].get<string>() << '\n';
                    prompt += (x["name"].get<string>() + " - " + x["description"].get<string>() + '\n');

                    if (a) {
                        cout << "\tUsage:\t" << x["usage"].get<string>() << '\n';
                        prompt += ("\tUsage:\t" + x["usage"].get<string>() + '\n');
                        cout << "\tExamples:\n";
                        prompt += ("\tExamples:\n");
                        for (auto ex : x["examples"]) {
                            cout << "\t\t" << ex.get<string>() << '\n';
                            prompt += ("\t\t" + ex.get<string>() + '\n');
                        }
                    }
                    cout << '\n';
                    prompt += '\n';
                }
            }

            popUpdisplaySetting(prompt, 0);
        }
        else {
            cout << commandData["invalid_command"]["prompt"].get<string>() << '\n';
            popUpdisplaySetting(commandData["invalid_command"]["prompt"].get<string>() + '\n', 0);
        }
    }
}

void eventHandler::rocketCardUseEntryPoint(int _playerIndex, int _duration) {
    if (_duration <= 0) return;
    processPlayer[turn]->disOwnCards(2);
    Player *player = processPlayer[_playerIndex];
    RocketCard::use(*player, _duration);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::diceCardUseEntryPoint(int _moveDistance) {
    processPlayer[turn]->disOwnCards(0);
    moveEntryPoint(_moveDistance);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::removeCardUseEntryPoint(QString _removeQStr) {
    string regisStr = _removeQStr.toStdString();
    int location = 0;
    for (int i = 0; i < 64; i++) {
        if (processMap[i]->getName() == regisStr) {
            location = i;
            break;
        }
    }
    processMap[location]->setLevel(0);
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    processPlayer[turn]->disOwnCards(3);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::roadBlockCardUseEnrtyPoint(QString _blockQStr) {
    string regisStr = _blockQStr.toStdString();
    regisStr = regisStr.substr(0, regisStr.find("."));
    int location = stoi(regisStr);
    Roadblock::use(*processMap[location]);
    processPlayer[turn]->disOwnCards(1);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::eventCardUseEntryPoint() {
    RandomEventCard::use(*processPlayer[turn]);
    processPlayer[turn]->disOwnCards(4);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

bool eventHandler::buyItemEntryPoint(int price, int itemIndex) {
    bool res = Shop::buyItem(processPlayer[turn], price, itemIndex);
    for (auto i: processPlayer[turn]->getOwnCards()) {
        cout << i << " ";
    }
    cout << endl;
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    return res;
}

void eventHandler::addMapPosXandPosY(double _posX, double _posY){
    mapPosXandPosY.push_back({_posX,_posY});
}

void eventHandler::clearMapPosXandPosY(){
    mapPosXandPosY.clear();
}


void eventHandler::movePointAnimator(int _step){
    int playerPos = processPlayer[turn]->getPos();
    int index = landCoordinate[playerPos];
    if(processPlayer[turn]->getPos() == 0){
        operateMovePoint.setChangeX(mapPosXandPosY[0].first);
        operateMovePoint.setChangeY(mapPosXandPosY[0].second);
    }
    double posX = mapPosXandPosY[index].first;
    double posY = mapPosXandPosY[index].second;
    hideSpecificPLayer(landCoordinate,m_mapList,processPlayer[turn],turn);
    operateMovePoint.initializeMovePoint(posX,posY,turn);
    emit movePointInitialize();
    std::thread t(&eventHandler::animationThread,this,_step,playerPos,index);
    t.detach();
}

void eventHandler::animationThread(int _times,int _playerPos,int _index){
    QMetaObject::invokeMethod(&operateMovePoint,"setIsvisable",Qt::QueuedConnection,Q_ARG(bool,true));

    bool origin = false;

    for(int i=0;i<_times;i++){

        if(processMap[_playerPos]->getState() == 1 || processPlayer[turn]->getState() == 1) break;

        if(processPlayer[turn]->getPos() == 63){
            origin = true;
            processPlayer[turn]->setPos(0);
            _playerPos = processPlayer[turn]->getPos();
            _index = landCoordinate[_playerPos];
        }
        else{
            _playerPos++;
            processPlayer[turn]->setPos(_playerPos);
            _index = landCoordinate[_playerPos];
        }
        operateMovePoint.movingMovePoint(mapPosXandPosY[_index].first,mapPosXandPosY[_index].second);

        // 原點處理
        if (origin && _playerPos == 0) {
            processPlayer[turn]->addMoney(8000);
        }
        else if (origin) {
            processPlayer[turn]->addMoney(4000);
        }
        QMetaObject::invokeMethod(this, "movePointStartMove", Qt::QueuedConnection);
        this_thread::sleep_for(chrono::milliseconds(400));
    }

    this_thread::sleep_for(chrono::milliseconds(250));
    QMetaObject::invokeMethod(&operateMovePoint, "hiddingMovePoint", Qt::QueuedConnection);
    QMetaObject::invokeMethod(this,"afterMove", Qt::QueuedConnection);
}

void eventHandler::afterMove(){
    int location = processPlayer[turn]->getPos();
    cout<<turn<<endl;

    // 確認種類是一般的已被擁有地塊且自己非擁有者
    if(processMap[location]->getType() == 0 && processMap[location]->getOwner() != turn && processMap[location]->getOwner() != -1)
        toll();
    //升級地塊或賣房
    else if(processMap[location]->getType() == 0 && processMap[location]->getOwner() == turn){
        popUpdisplaySetting("",2);
    }
    //買房
    else if(processMap[location]->getType() == 0 && processMap[location]->getOwner() == -1){
        popUpdisplaySetting("",1);
    }
    // 事件地塊
    else if (processMap[location]->getType() == 1) {
        // buttonState = false;
        // QMetaObject::invokeMethod(this, "EnableChanged", Qt::QueuedConnection);
        //=================往後加=================
    }
    // 商店
    else if (processMap[location]->getType() == 2) {
        emit openShopPopup();
    }
    // 解除路障
    if (processMap[location]->getState() == 1)
        processMap[location]->setState(0);

    // if (processMap[location]->getType() != 0) {
    //     buttonState = false;
    //     emit EnableChanged();
    // }
    // nextTurn();
}

void eventHandler::nextTurn(){
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    turn = (turn + 1) % 4;
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::toll() {
    int nowPos = processPlayer[turn]->getPos();
    int landOwner = processMap[nowPos]->getOwner();
    int landValue = processMap[nowPos]->getValue();
    int nowLevel = processMap[nowPos]->getLevel();
    int fee = (nowLevel) * (landValue / 10);
    processPlayer[turn]->subMoney(fee);
    processPlayer[landOwner]->addMoney(fee);
    popUpdisplaySetting("-"+to_string(fee),0);
}

void eventHandler::buyLand() {
    if (turn >= 0) {
        int nowPos = processPlayer[turn]->getPos();
        if (processMap[nowPos]->getType() == 0 && processMap[nowPos]->getOwner() == 0) {
            processPlayer[turn]->addHouse(nowPos);
            processMap[nowPos]->setOwner(turn + 1);
            processMap[nowPos]->setLevel(1);
            processPlayer[turn]->subMoney(processMap[nowPos]->getValue());
            buttonState = false;
            emit EnableChanged();
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
            mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
        }
    }
}

void eventHandler::levelup() {
    if (turn >= 0) {
        int nowPos = processPlayer[turn]->getPos();
        if (processMap[nowPos]->getType() == 0 && processMap[nowPos]->getOwner() == turn + 1 && processMap[nowPos]->
                                                                                                    getLevel() < 4) {
            int nowLevel = processMap[nowPos]->getLevel();
            processMap[nowPos]->setLevel(nowLevel + 1);
            processPlayer[turn]->subMoney(processMap[nowPos]->getValue() / 2);
            buttonState = false;
            emit EnableChanged();
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
            mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
        }
    }
}

void eventHandler::sellLand() {
    if (turn >= 0) {
        int nowPos = processPlayer[turn]->getPos();
        if (processMap[nowPos]->getType() == 0 && processMap[nowPos]->getOwner() == turn + 1) {
            int value = processMap[nowPos]->getValue();
            processMap[nowPos]->setOwner(0);
            processMap[nowPos]->setLevel(0);
            processPlayer[turn]->addMoney((value / 2) + (processMap[nowPos]->getLevel() * value / 2));
            buttonState = false;
            emit EnableChanged();
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
            mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
        }
    }
}

void eventHandler::popUpdisplaySetting(string _message,int _type){
    cout<<"in popUpdisplaySetting"<<endl;
    if(_type == 0){
        setDisplayMessage(QString::fromStdString(_message));
        emit openMessage();
    }
    else if(_type == 1){
        string message = "You arrive "+ processMap[processPlayer[turn]->getPos()]->getName() +".";
        setDisplayMessage(QString::fromStdString(message));
        emit openBuyPopup();
    }
    else if(_type == 2){
        string message = processMap[processPlayer[turn]->getPos()]->getName() +" is your own place.";
        bool isUpgradeable = true ,isSellable = true;
        setDisplayMessage(QString::fromStdString(message));
        if(processMap[processPlayer[turn]->getPos()]->getLevel() < 4)
            isUpgradeable = false;
        if(processMap[processPlayer[turn]->getPos()]->getLevel() > 0)
            isSellable = false;
        emit openUpgradePopup(isUpgradeable,isSellable);
    }
}

QString eventHandler::displayMessage() const
{
    return m_displayMessage;
}

void eventHandler::setDisplayMessage(const QString &newDisplayMessage)
{
    if (m_displayMessage == newDisplayMessage)
        return;
    m_displayMessage = newDisplayMessage;
    emit displayMessageChanged();
}
