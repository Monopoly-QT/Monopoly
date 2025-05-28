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
#include <cstdlib>
#include <ctime>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <random>
#include <queue>
#include <algorithm>
#include "../Hospital/Hospital.h"
#include "Land/Land.h"

#include "Handler/MapHandler/mapHandler.h"
#include "ItemCard/DestroyImmovableCard/DestroyImmovableCard.h"
#include "ItemCard/DiceControl/DiceControlCard.h"
#include "ItemCard/RandomEventCard/RandomEventCard.h"
#include "ItemCard/RoadblockCard/RoadblockCard.h"
#include "ItemCard/RocketCard/RocketCard.h"
#include "Shop/shop.h"
#include "MiniGames/DragonGate/DragonGate.h"
#include "MiniGames/HorseRacing/HorseRacing.h"


bool checkNum(string needChecked) {
    for (int i = 0; i < needChecked.size(); i++) {
        if (!isdigit(needChecked[i])) {
            return false;
        }
    }

    return true;
}

eventHandler::eventHandler(QQmlApplicationEngine *engine) {
    this->engine = engine;

    // 東西都移到restart()裡面了
    restart(true);
}

eventHandler::~eventHandler() {
    for (auto i: processMap) {
        delete i;
    }
    for (auto i: processPlayer) {
        delete i;
    }
    processMap.clear();
    processPlayer.clear();
}

void eventHandler::restart(bool first) {
    if (!first) {
        firstClick = true;
        for (auto i: processMap) {
            delete i;
        }
        for (auto i: processPlayer) {
            delete i;
        }
        processMap.clear();
        processPlayer.clear();
    }

    turn = 0;

    nlohmann::json countryData;
    ifstream country;
    country.open("json/country.json");

    if (country.fail()) {
        cout << "Falied to open country.json\n";
    }

    country >> countryData;
    country.close();

    for (int i = 0; i < 64; i++) {
        Land *regis = new Land(countryData[to_string(i)]["type"].get<int>(), i,
                               countryData[to_string(i)]["name"].get<string>(),
                               countryData[to_string(i)]["value"].get<int>(),
                               countryData[to_string(i)]["translation"].get<string>());
        regis->setLevel(0);
        Land::landNameToPos[regis->getName()] = i;
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

    m_endMoney = playerData["End"]["money"].get<int>();

    for (int i = 0; i < 4; i++) {
        vector<int> ownCardFromConfig;
        string strOwnCardFromConfig = playerData[to_string(i)]["ownCard"].get<string>();
        stringstream ss(strOwnCardFromConfig);
        while (ss >> strOwnCardFromConfig) {
            ownCardFromConfig.push_back(stoi(strOwnCardFromConfig));
        }
        Player *regis = new Player(playerData[to_string(i)]["money"].get<int>(),
                                   playerData[to_string(i)]["playerID"].get<int>(),
                                   playerData[to_string(i)]["playerName"].get<string>(),
                                   playerData[to_string(i)]["playerLastName"].get<string>(), ownCardFromConfig,
                                   playerData[to_string(i)]["pos"].get<int>(),
                                   playerData[to_string(i)]["state"].get<int>(),
                                   playerData[to_string(i)]["stayInHospitalTurn"].get<int>(),
                                   playerData[to_string(i)]["nextRollDicePoint"].get<int>());
        processPlayer.push_back(regis);

        playerNameToID[regis->getPlayerLastName()] = regis->getID();
    }

    mapInitialize(landCoordinate, m_mapList, processMap, processPlayer);
    m_movePoint = &operateMovePoint;
    m_displayState = new StateDisplay();
    m_useCard = new UseCardSetting();

    processPlayer[2]->setPos(18);
    processMap[5]->setOwner(0);
    processMap[5]->setLevel(4);
    processPlayer[0]->addOwnImmovables(5);
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);


    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    btnEnableSetting(true);

    emit mapListChanged();
    emit movePointChanged();
    emit movePointStartMove();
    emit movePointInitialize();
    emit displayStateChanged();
    emit useCardChanged();
    emit displayMessageChanged();
}

int eventHandler::getTurn() {
    return turn;
}

int eventHandler::getHosiptalRemainingDays(){
    return Hospital::getDayInHospital(processPlayer[turn]);
}

void eventHandler::leaveEarly(){
    processPlayer[turn]->subMoney(Hospital::getDayInHospital(processPlayer[turn]) * 1000);
    Hospital::leaveHospital(processPlayer[turn]);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::moveEntryPoint(int _moveDistance) {
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    if (processPlayer[turn]->getState() == 0)movePointAnimator(_moveDistance);
    else {
        Hospital::update(processPlayer[turn]);
        if (_moveDistance >= 8){
            Hospital::leaveHospital(processPlayer[turn]);
        }
        nextTurn();
    }
}

void eventHandler::commendEntryPoint(QString _instruct) {
    string strInstruct = _instruct.toStdString();

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
                if (stoi(inputCommand) < 0) {
                    cout << "\n\nError: Pos should be larger than 0\n";
                    popUpdisplaySetting("Error: Pos should be larger than 0\n", 0);
                    return;
                }

                processPlayer[turn]->addPos(stoi(inputCommand));
                regex r(R"(\{location\})");
                prompt = regex_replace(prompt, r, to_string(processPlayer[turn]->getPos()));
                mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
                cout << prompt << '\n';
                popUpdisplaySetting(prompt, 0);

                afterMove();
            } else if (inputCommand == "to") {
                ss >> inputCommand;
                if (checkNum(inputCommand) && stoi(inputCommand) >= 0 && stoi(inputCommand) <= 63) {
                    int newPos = stoi(inputCommand) % 64;
                    processPlayer[turn]->setPos(newPos);
                    regex r(R"(\{location\})");
                    prompt = regex_replace(prompt, r, to_string(newPos));
                    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
                    cout << prompt << '\n';
                    popUpdisplaySetting(prompt, 0);

                    afterMove();
                } else {
                    cout << "Error: Pos should be between 0 to 63\n";
                    popUpdisplaySetting("Error: Pos should be between 0 to 63\n", 0);

                    return;
                }
            } else {
                cout << "Error: Command should be \"/move [pos]\" or \"/move to [pos]";
                popUpdisplaySetting("Error: Command should be \"/move [pos]\" or \"/move to [pos]", 0);

                return;
            }
        } else if (inputCommand == "/give") {
            prompt = commandData["give"]["prompt"].get<string>();

            string payee;
            ss >> payee;

            bool valid = 0;
            for (int i = 0; i < 4; i++) {
                if (payee == processPlayer[i]->getPlayerLastName()) {
                    valid = 1;
                }
            }

            if (!valid) {
                cout << "Error: Not found a player's lastname is " + payee;
                popUpdisplaySetting("Error: Not found a player's lastname is " + payee, 0);

                return;
            }

            regex r1(R"(\{playerName\})");
            prompt = regex_replace(prompt, r1, payee);

            ss >> inputCommand;
            int deltaMoney = stoi(inputCommand);
            regex r2(R"(\{money\})");
            prompt = regex_replace(prompt, r2, to_string(deltaMoney));

            if (processPlayer[turn]->getMoney() < deltaMoney) {
                cout << "Error: " << processPlayer[turn]->getPlayerName() << "don't have enough money.\n";
                popUpdisplaySetting("Error: " + processPlayer[turn]->getPlayerName() + "don't have enough money.\n", 0);

                return;
            }

            if (deltaMoney < 0) {
                cout << "Error: The money should be larger than 0";
                popUpdisplaySetting("Error: The money should be larger than 0", 0);
            }

            processPlayer[turn]->subMoney(deltaMoney);
            processPlayer[playerNameToID[payee]]->addMoney(deltaMoney);
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            cout << prompt << '\n';
            popUpdisplaySetting(prompt, 0);
        } else if (inputCommand == "/get") {
            prompt = commandData["get"]["prompt"].get<string>();
            ss >> inputCommand;
            if (checkNum(inputCommand) && stoi(inputCommand) > 0) {
                int deltaMoney = stoi(inputCommand);
                regex r1(R"(\{playerName\})");
                prompt = regex_replace(prompt, r1, processPlayer[turn]->getPlayerName());
                regex r2(R"(\{money\})");
                prompt = regex_replace(prompt, r2, to_string(deltaMoney));
                processPlayer[turn]->addMoney(deltaMoney);
                m_displayState->initialStateDisplay(turn, processPlayer[turn]);
                cout << prompt << '\n';
                popUpdisplaySetting(prompt, 0);
            } else {
                cout << "Error: The money should be larger than 0";
                popUpdisplaySetting("Error: The money should be larger than 0", 0);

                return;
            }
        } else if (inputCommand == "/card") {
            nlohmann::json cardData;
            ifstream card;
            card.open("json/card.json");

            if (card.fail()) {
                cout << "Falied to open card.json\n";
            }

            card >> cardData;
            card.close();

            prompt = commandData["card"]["prompt"].get<string>();
            ss >> inputCommand;

            bool found = false;

            for (int i = 0; i < 5; i++) {
                if (cardData["IDToName"][to_string(i)]["name"] == inputCommand) {
                    found = true;
                }
            }

            if (!found) {
                popUpdisplaySetting("Error: No card called " + inputCommand + '.', 0);

                return;
            }

            processPlayer[turn]->addOwnCards(cardData["NameToID"][inputCommand]["ID"].get<int>());
            m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
            regex r(R"(\{card_name\})");
            prompt = regex_replace(prompt, r, inputCommand);
            cout << prompt << '\n';
            popUpdisplaySetting(prompt, 0);
        } else if (inputCommand == "/minigame") {
            prompt = commandData["minigame"]["prompt"].get<string>();
            cout << prompt << '\n';

            ss >> inputCommand;
            if (inputCommand == "DragonGate") {
                regex r(R"(\{minigame_name\})");
                prompt = regex_replace(prompt, r, inputCommand);
                popUpdisplaySetting(prompt, 0);

                // Enter DragonGate
                dragonGateGameObject.init(processPlayer[turn]);
                engine->rootContext()->setContextProperty("gameClass", &dragonGateGameObject);
                engine->rootContext()->setContextProperty("playerClass", processPlayer[turn]);
                emit openDragonGate();
            } else if (inputCommand == "HorseRacing") {
                regex r(R"(\{minigame_name\})");
                prompt = regex_replace(prompt, r, inputCommand);
                popUpdisplaySetting(prompt, 0);
                if (processPlayer[turn]->getMoney() <= 0) {
                    emit openBankruptcy();
                }

                // Enter HorseRacing
                horseRacingGameObject.init(processPlayer[turn]);
                engine->rootContext()->setContextProperty("gameClass", &horseRacingGameObject);
                engine->rootContext()->setContextProperty("playerClass", processPlayer[turn]);
                emit openHorseRacing();
            } else {
                cout << "Error: No minigame called " + inputCommand;
                popUpdisplaySetting("Error: No minigame called " + inputCommand, 0);

                return;
            }
        } else if (inputCommand == "/info") {
            string colors[4] = {"Red", "Blue", "Green", "Yellow"};
            string prompt = "Players' Information: \n\n";
            cout << commandData["info"]["prompt"].get<string>();
            for (int i = 0; i < 4; i++) {
                prompt += "ID: " + to_string(processPlayer[i]->getID()) + "\n";
                prompt += "Color: " + colors[i] + "\n";
                prompt += "Name: " + processPlayer[i]->getPlayerName() + "\n";
                prompt += "Last Name: " + processPlayer[i]->getPlayerLastName() + "\n";
                prompt += "Life: " + string(processPlayer[i]->getIsLive() ? "Alive\n" : "Dead\n");
                prompt += "Money: " + to_string(processPlayer[i]->getMoney()) + "\n";
                prompt += "Position: " + to_string(processPlayer[i]->getPos()) + " " + processMap[processPlayer[i]->
                    getPos()]->getName() + "\n";
                prompt += "Land(s): \n";
                vector<int> tempV = processPlayer[i]->getOwnImmovables();

                if(tempV.empty()){
                    prompt += "\tNone\n";
                }
                else{
                    sort(tempV.begin(),tempV.end());

                    for (int i = 0; i < tempV.size(); i++) {
                        prompt += "\tPosition: " + to_string(tempV[i]) + "\n\t " + processMap[tempV[i]]->getName() +
                                "\n\tLevel: " + to_string(processMap[tempV[i]]->getLevel()) + "\n";
                    }
                }

                prompt += "Card(s): \n";

                nlohmann::json cardData;
                ifstream card;
                card.open("json/card.json");

                if (card.fail()) {
                    cout << "Falied to open card.json\n";
                }

                card >> cardData;
                card.close();

                tempV = processPlayer[i]->getOwnCards();

                if(tempV.empty()){
                    prompt += "\tNone\n";
                }
                else{
                    sort(tempV.begin(),tempV.end());

                    for (int i = 0; i < tempV.size(); i++) {
                        prompt += "\t" + cardData["IDToName"][to_string(tempV[i])]["name"].get<string>() + string(
                            i == tempV.size() - 1 ? "\n" : ",\n");
                    }
                }

                prompt += "Status: " + string(processPlayer[i]->getState() ? "In" : "Not in") + " the hospital\n";
                prompt += "Hospitalization time: " + to_string(processPlayer[i]->GetstayInHospitalTurn()) +
                        " day(s) remaining\n";
                prompt += "\n";
            }

            popUpdisplaySetting(prompt, 0);
        } else if (inputCommand == "/refresh") {
            cout << commandData["refresh"]["prompt"].get<string>();
            emit startRefresh();
        } else if (inputCommand == "/list" || inputCommand == "/help") {
            string prompt;
            bool a = false;

            if (ss >> inputCommand) {
                if (inputCommand == "-a") {
                    a = true;
                }
            }

            for (auto x: commandData) {
                if (x["name"].get<string>() != "") {
                    cout << x["name"].get<string>() << " - " << x["description"].get<string>() << '\n';
                    prompt += (x["name"].get<string>() + " - " + x["description"].get<string>() + '\n');

                    if (a) {
                        cout << "\tUsage:\t" << x["usage"].get<string>() << '\n';
                        prompt += ("\tUsage:\t" + x["usage"].get<string>() + '\n');
                        cout << "\tExamples:\n";
                        prompt += ("\tExamples:\n");
                        for (auto &ex: x["examples"]) {
                            cout << "\t\t" << ex.get<string>() << '\n';
                            prompt += ("\t\t" + ex.get<string>() + '\n');
                        }
                    }
                    cout << '\n';
                    prompt += '\n';
                }
            }

            popUpdisplaySetting(prompt, 0);
        } else {
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
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
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

void eventHandler::sellLandFromStrUseEntryPoint(QString _removeQStr) {
    string regisStr = _removeQStr.toStdString();
    int location = 0;
    for (int i = 0; i < 64; i++) {
        if (processMap[i]->getName() == regisStr) {
            location = i;
            break;
        }
    }

    if (turn >= 0) {
        if (processMap[location]->getType() == 0 && processMap[location]->getOwner() == turn + 1) {
            int value = processMap[location]->getValue();
            processPlayer[turn]->addMoney((value / 2) + (processMap[location]->getLevel() * value / 2));
            processMap[location]->setOwner(-1);
            processMap[location]->setLevel(0);
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
            mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
        }
    }
}

void eventHandler::sellLandFromStrUseWhenDieEntryPoint(QString _removeQStr) {
    string regisStr = _removeQStr.toStdString();
    cout<<"SELL"<<regisStr<<endl;
    int location = 0;
    for (int i = 0; i < 64; i++) {
        if (processMap[i]->getName() == regisStr) {
            location = i;
            break;
        }
    }

    if (turn >= 0) {
        if (processMap[location]->getType() == 0 && processMap[location]->getOwner() == turn) {
            int value = processMap[location]->getValue();
            cout<<"VALUE"<<value<<endl;
            processPlayer[turn]->addMoney((value / 2) + (processMap[location]->getLevel() * value / 2));
            processMap[location]->setOwner(-1);
            processMap[location]->setLevel(0);
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
            m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
            mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
        }
    }
}

void eventHandler::roadBlockCardUseEnrtyPoint(QString _blockQStr) {
    string regisStr = _blockQStr.toStdString();
    regisStr = regisStr.substr(0, regisStr.find("."));
    int location = stoi(regisStr);
    Roadblock::use(*processMap[location]);
    processPlayer[turn]->disOwnCards(1);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
}

void eventHandler::eventCardUseEntryPoint() {
    randomEvent();
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

void eventHandler::addMapPosXandPosY(double _posX, double _posY) {
    mapPosXandPosY.push_back({_posX, _posY});
}

void eventHandler::clearMapPosXandPosY() {
    mapPosXandPosY.clear();
}


void eventHandler::movePointAnimator(int _step) {
    int playerPos = processPlayer[turn]->getPos();
    int index = landCoordinate[playerPos];
    if (processPlayer[turn]->getPos() == 0) {
        operateMovePoint.setChangeX(mapPosXandPosY[0].first);
        operateMovePoint.setChangeY(mapPosXandPosY[0].second);
    }
    double posX = mapPosXandPosY[index].first;
    double posY = mapPosXandPosY[index].second;
    hideSpecificPLayer(landCoordinate, m_mapList, processPlayer[turn], turn);
    operateMovePoint.initializeMovePoint(posX, posY, turn);
    emit movePointInitialize();
    std::thread t(&eventHandler::animationThread, this, _step, playerPos, index);
    t.detach();
}

void eventHandler::animationThread(int _times, int _playerPos, int _index) {
    QMetaObject::invokeMethod(&operateMovePoint, "setIsvisable", Qt::QueuedConnection,Q_ARG(bool, true));

    origin = false;

    // _times = 2;
    for (int i = 0; i < _times; i++) {
        if (processMap[_playerPos]->getState() == 1 || processPlayer[turn]->getState() == 1) break;

        if (processPlayer[turn]->getPos() == 63) {
            origin = true;
            processPlayer[turn]->setPos(0);
            _playerPos = processPlayer[turn]->getPos();
            _index = landCoordinate[_playerPos];
        } else {
            _playerPos++;
            processPlayer[turn]->setPos(_playerPos);
            _index = landCoordinate[_playerPos];
        }
        operateMovePoint.movingMovePoint(mapPosXandPosY[_index].first, mapPosXandPosY[_index].second);

        QMetaObject::invokeMethod(this, "movePointStartMove", Qt::QueuedConnection);
        this_thread::sleep_for(chrono::milliseconds(400));
    }

    this_thread::sleep_for(chrono::milliseconds(250));
    QMetaObject::invokeMethod(&operateMovePoint, "hiddingMovePoint", Qt::QueuedConnection);
    QMetaObject::invokeMethod(this, "afterMove", Qt::QueuedConnection);
}

void eventHandler::afterMove() {
    qDebug()<<turn<<"\n";
    int location = processPlayer[turn]->getPos();
    int landOwner = processMap[location]->getOwner();

    if(origin){
        if(location == 0){
            processPlayer[turn]->addMoney(4000);
            popUpdisplaySetting("+4000", 0);
        }else{
            processPlayer[turn]->addMoney(2000);
            popUpdisplaySetting("+2000", 0);
        }
        origin = false;
    }
    // 解除路障
    if (processMap[location]->getState() == 1) {
        processMap[location]->setState(0);
        mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    } else {
        mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    }

    // 確認種類是一般的已被擁有地塊且自己非擁有者
    if (processMap[location]->getType() == 0 && landOwner != turn && processMap[location]->getOwner() != -1)
        toll();
        //升級地塊或賣房
    else if (processMap[location]->getType() == 0 && landOwner == turn) {
        m_displayState->getlandValue1(processMap[location]->getValue() / 2);
        m_displayState->getlandValue2(
            (processMap[location]->getValue() / 2) + (
                processMap[location]->getLevel() * processMap[location]->getValue() / 2));
        popUpdisplaySetting("", 2);
    }
    //買房
    else if (processMap[location]->getType() == 0 && processMap[location]->getOwner() == -1) {
        m_displayState->getlandValue1(processMap[location]->getValue());
        popUpdisplaySetting("", 1);
    }
    // 事件地塊
    else if (processMap[location]->getType() == 1) {
        randomEvent();
    }
    // 商店
    else if (processMap[location]->getType() == 2) {
        emit openShopPopup();
    }
    // Hospital & 其他
    else {
        nextTurn();
    }
}

void eventHandler::randomEvent() {
    nlohmann::json countryData;
    ifstream country;
    country.open("json/country.json");

    if (country.fail()) {
        cout << "Falied to open country.json\n";
    }

    country >> countryData;
    country.close();

    nlohmann::json eventData;
    ifstream event;
    event.open("json/event.json");

    if (event.fail()) {
        cout << "Falied to open event.json\n";
    }

    event >> eventData;
    event.close();

    random_device rd;
    srand(rd());

    int randNum = rand() % 250;
    int eventNum = (randNum < 199 ? randNum : 199);

    cout << "Event " << eventNum << '\n';
    cout << eventData[to_string(eventNum)]["text"].get<string>() << '\n';
    popUpdisplaySetting(eventData[to_string(eventNum)]["text"].get<string>() + "\n", 0);

    string function = eventData[to_string(eventNum)]["function"].get<string>();
    cout << function;

    stringstream ssfun(function);
    while (ssfun >> function) {
        if (function == "sub") {
            int delta;
            ssfun >> delta;
            processPlayer[turn]->subMoney(delta);
            nextTurn();
        } else if (function == "add") {
            int delta;
            ssfun >> delta;
            processPlayer[turn]->addMoney(delta);
            nextTurn();
        } else if (function == "level") {
            int newLevel;
            ssfun >> newLevel;
            string area;

            while (ssfun >> area) {
                if (area != "end") {
                    processMap[Land::landNameToPos[area]]->setLevel(newLevel);
                } else {
                    break;
                }
            }
            nextTurn();
        } else if (function == "hospital") {
            int day;
            ssfun >> day;
            processPlayer[turn]->setStayInHospitalTurn(day);
            processPlayer[turn]->setPos(min(abs(32 - processPlayer[turn]->getPos()),
                                            abs(63 - processPlayer[turn]->getPos())));
            afterMove();
            // nextTurn();
        } else if (function == "fly") {
            string area;
            ssfun >> area;
            processPlayer[turn]->setPos(Land::landNameToPos[area]);
            mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
            afterMove();
            // nextTurn();
        } else if (function == "run") {
            // this_thread::sleep_for(chrono::milliseconds(1000));

            random_device rd;
            srand(rd());
            int minigameNum = rand() % 2;

            if (minigameNum) {
                // Enter DragonGate
                dragonGateGameObject.init(processPlayer[turn]);
                engine->rootContext()->setContextProperty("gameClass", &dragonGateGameObject);
                engine->rootContext()->setContextProperty("playerClass", processPlayer[turn]);
                emit openDragonGate();
            } else {
                // Enter HorseRacing
                horseRacingGameObject.init(processPlayer[turn]);
                engine->rootContext()->setContextProperty("gameClass", &horseRacingGameObject);
                engine->rootContext()->setContextProperty("playerClass", processPlayer[turn]);
                emit openHorseRacing();
            }
        }
    }
}

void eventHandler::nextTurn() {
    turn = (turn + 1) % 4;
    int tmp = turn;
    while (!processPlayer[turn]->getIsLive()) {
        turn = (turn + 1) % 4;
        if (tmp == turn) {
            break; // 所有玩家都死了
        }
    }
    if (checkIsGameEnded()) {
        return;
    }

    if (processPlayer[turn]->getMoney() <= 0) {
        setDisplayMessage_bankruptcypopUp("Bankrupt!");
        emit openBankruptcy();
    }

    if(Hospital::isInHospital(processPlayer[turn])){
        emit openHospitalPopups();
    }

    btnEnableSetting(true);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}

void eventHandler::gameEnd() {
    string display = "";
    for (int i = 0; i < 4; i++) {
        if (processPlayer[i]->getMoney() >= m_endMoney) {
            display += processPlayer[i]->getPlayerName() + " WINS!\n";
        }
    }

    for (int i = 0; i < 4; i++) {
        display += processPlayer[i]->getPlayerName() + ": " +
                (processPlayer[i]->getIsLive() ? "Alive" : "Dead") + "($ " + to_string(processPlayer[i]->getMoney()) +
                ")\n";
    }
    display += "\nDo you wanna start a new game?";
    popUpdisplaySetting(display, 3);
    btnEnableSetting(true);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    return;
}


void eventHandler::suicidal() {
    processPlayer[turn]->setIsLive(false);
    vector<int> ownPos;
    for(auto i:processPlayer[turn]->getOwnImmovables()){
        ownPos.push_back(i);
    }
    for(auto i:ownPos){
        processMap[i]->setOwner(-1);
        processMap[i]->setLevel(0);
        processPlayer[turn]->removeOwnImmovables(i);
    }
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    nextTurn();
}

void eventHandler::updateState() {
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    checkIsBankrupt();
    checkIsGameEnded();
}

bool eventHandler::checkIsGameEnded() {
    int liveCount = 0;
    for (int i = 0; i < 4; i++) {
        if (processPlayer[i]->getIsLive()) {
            liveCount++;
        }
        if (processPlayer[i]->getMoney() >= m_endMoney) {
            qDebug()<<i<<" "<<processPlayer[i]->getMoney()<<"\n";
            gameEnd();
            return true;
        }
    }

    if (liveCount <= 1) {
        gameEnd();
        return true;
    }
    return false;
}


bool eventHandler::checkIsBankrupt() {
    if (processPlayer[turn]->getMoney() <= 0) {
        emit openBankruptcy();
        return true;
    }
    return false;
}

/*  land owner is turn+1 */

void eventHandler::toll() {
    int nowPos = processPlayer[turn]->getPos();
    int landOwner = processMap[nowPos]->getOwner();
    int landValue = processMap[nowPos]->getValue();
    int nowLevel = processMap[nowPos]->getLevel();
    int fee = (nowLevel) * (landValue / 10);
    processPlayer[turn]->subMoney(fee);
    processPlayer[landOwner]->addMoney(fee);
    popUpdisplaySetting("-" + to_string(fee), 0);
    nextTurn();
}

void eventHandler::buyLand() {
    qDebug() << "run";

    int nowPos = processPlayer[turn]->getPos();
    if (processPlayer[turn]->getMoney() >= processMap[nowPos]->getValue()) {
        processPlayer[turn]->addHouse(nowPos);
        processPlayer[turn]->addOwnImmovables(nowPos);
        processMap[nowPos]->setOwner(turn);
        processMap[nowPos]->setLevel(1);
        processPlayer[turn]->subMoney(processMap[nowPos]->getValue());
        m_displayState->initialStateDisplay(turn, processPlayer[turn]);
        m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
        mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
        qDebug()<<"landOwner is "<<processMap[processPlayer[1]->getPos()]->getOwner()<<"\n\n";
    }
    else popUpdisplaySetting("oops, you don't have enough money", 0);
    nextTurn();
}

void eventHandler::levelup() {
    int nowPos = processPlayer[turn]->getPos();
    if (processPlayer[turn]->getMoney() >= (processMap[nowPos]->getValue() / 2) && processMap[nowPos]->getLevel() < 4) {
        int nowLevel = processMap[nowPos]->getLevel();
        processMap[nowPos]->setLevel(nowLevel + 1);
        processPlayer[turn]->subMoney(processMap[nowPos]->getValue() / 2);
        m_displayState->initialStateDisplay(turn, processPlayer[turn]);
        m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
        mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    }
    else if(processMap[nowPos]->getLevel() == 4) popUpdisplaySetting("oops, the level is already maxed out", 0);
    else if(processPlayer[turn]->getMoney() < (processMap[nowPos]->getValue() / 2))popUpdisplaySetting("oops, you don't have enough money", 0);

    nextTurn();
}

void eventHandler::sellLand() {
    int nowPos = processPlayer[turn]->getPos();
    int value = processMap[nowPos]->getValue();
    processPlayer[turn]->addMoney((value / 2) + (processMap[nowPos]->getLevel() * value / 2));
    processMap[nowPos]->setOwner(-1);
    processMap[nowPos]->setLevel(0);
    processPlayer[turn]->removeOwnImmovables(nowPos);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    nextTurn();
}

void eventHandler::popUpdisplaySetting(string _message, int _type) {
    if (_type == 0) {
        setDisplayMessage_messagePopup(QString::fromStdString(_message));
        emit openMessage();
    } else if (_type == 1) {
        string message = "You arrive " + processMap[processPlayer[turn]->getPos()]->getName() + ".";
        setDisplayMessage_buyPopup(QString::fromStdString(message));
        emit openBuyPopup();
    } else if (_type == 2) {
        string message = processMap[processPlayer[turn]->getPos()]->getName() + " is your own place.";
        bool isUpgradeable = true, isSellable = true;
        setDisplayMessage_upgradePopup(QString::fromStdString(message));
        if (processMap[processPlayer[turn]->getPos()]->getLevel() < 4)
            isUpgradeable = false;
        if (processMap[processPlayer[turn]->getPos()]->getLevel() > 0)
            isSellable = false;
        emit openUpgradePopup(isUpgradeable, isSellable);
    } else if (_type == 3) {
        setDisplayMessage_endPopup(QString::fromStdString(_message));
        emit openEndPopup();
    }
}

void eventHandler::btnEnableSetting(bool _isEnable)
{
    m_diceEnabled = _isEnable;
    m_cardEnabled = _isEnable;
    m_cheatEnable = _isEnable;
    emit diceEnabledChanged();
    emit cardEnabledChanged();
    emit cheatEnableChanged();
    //:D
}
