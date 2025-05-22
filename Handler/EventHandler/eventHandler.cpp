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
#include "../Hospital/Hospital.h"

#include "Handler/MapHandler/mapHandler.h"
#include "ItemCard/DiceControl/DiceControlCard.h"

bool checkNum(string needChecked) {
    for (int i = 0; i < needChecked.size(); i++) {
        if (!isdigit(needChecked[i])) {
            return false;
        }
    }

    return true;
}

// void runMinigame();

// void initialize();

// void start();

// void finish();

// void printAllPlayerInfo();

// void refresh();

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

        playerNameToID[regis->getPlayerLastName()] = regis->getID();
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

    cin >> ws;
    while (getline(cin, inputCommand)) {
        stringstream ss(inputCommand);
        while (ss >> inputCommand) {
            if (inputCommand == "/move") {
                prompt = commandData["move"]["prompt"].get<string>();
                regex r1(R"(\{playerName\})");
                prompt = regex_replace(prompt, r1, processPlayer[turn]->getPlayerLastName());
                ss >> inputCommand;
                if (checkNum(inputCommand)) {
                    processPlayer[turn]->addPos(stoi(inputCommand));
                    regex r(R"(\{location\})");
                    prompt = regex_replace(prompt, r, to_string(processPlayer[turn]->getPos()));
                    cerr << prompt << '\n';
                }
                else if (inputCommand == "to") {
                    ss >> inputCommand;
                    if (checkNum(inputCommand) && stoi(inputCommand) <= 64) {
                        int newPos = stoi(inputCommand) % 64;
                        processPlayer[turn]->setPos(newPos);
                        regex r(R"(\{location\})");
                        prompt = regex_replace(prompt, r, to_string(newPos));
                        cout << prompt << '\n';
                    }
                    else {
                        cout << "Valid input!\n";
                        break;
                    }
                }
                else {
                    cout << "Valid input!\n";
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
                    break;
                }

                regex r1(R"(\{playerName\})");
                prompt = regex_replace(prompt, r1, payee);

                ss >> inputCommand;
                int deltaMoney = stoi(inputCommand);
                regex r2(R"(\{money\})");
                prompt = regex_replace(prompt, r2, to_string(deltaMoney));

                if (processPlayer[turn]->getMoney() < deltaMoney) {
                    cout << "Valid input!\n";
                    break;
                }

                processPlayer[turn]->subMoney(deltaMoney);
                processPlayer[playerNameToID[payee]]->addMoney(deltaMoney);
                cout << prompt << '\n';
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
                    cout << prompt << '\n';
                }
                else {
                    cout << "Valid input!\n";
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
            // else if (inputCommand == "/minigame") {
            //     prompt = commandData["minigame"]["prompt"].get<string>();
            //     cout << prompt << '\n';
            //     ss >> inputCommand;
            //     runMinigame();
            // }
            // else if (inputCommand == "/gamestate") {
            //     prompt = commandData["gamestate"]["prompt"].get<string>();
            //     ss >> inputCommand;
            //     if (inputCommand == "INIT") {
            //         initialize();
            //     }
            //     else if (inputCommand == "START") {
            //         start();
            //     }
            //     else if (inputCommand == "MOVED") {
            //         moved();
            //     }
            //     else if (inputCommand == "FINISH") {
            //         finish();
            //     }
            //     regex r(R"(\{state\})");
            //     prompt = regex_replace(prompt, r, inputCommand);
            //     cout << prompt << '\n';
            // }
            // else if (inputCommand == "/info") {
            //     cout << commandData["info"]["prompt"].get<string>();
            //     printAllPlayerInfo();
            // }
            // else if (inputCommand == "/refresh") {
            //     cout << commandData["refresh"]["prompt"].get<string>();
            //     refresh();
            // }
            else if (inputCommand == "/list" || inputCommand == "/help") {
                bool a = false;
                if (ss >> inputCommand) {
                    if (inputCommand == "-a") {
                        a = true;
                    }
                }
                for (auto x : commandData) {
                    if (x["name"].get<string>() != "") {
                        cout << x["name"].get<string>() << " - " << x["description"].get<string>() << '\n';

                        if (a) {
                            cout << "\tUsage:\t" << x["usage"].get<string>() << '\n';
                            cout << "\tExamples:\n";
                            for (auto ex : x["examples"]) {
                                cout << "\t\t" << ex.get<string>() << '\n';
                            }
                        }
                        cout << '\n';
                    }
                }
            }
            else {
                cout << commandData["invalid_command"]["prompt"].get<string>() << '\n';
            }
        }
    }
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
