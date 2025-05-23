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

// void moved();

// void finish();

// void printAllPlayerInfo();

// void refresh(){
//     // 假設你在 eventHandler 中有 MainWindow 的 QObject 指標
//     QMetaObject::invokeMethod(mainQmlRootObject, "showRefresh", Qt::QueuedConnection);
// }

eventHandler::eventHandler() {
    turn = 0;

    nlohmann::json countryData;
    ifstream country;
    country.open("json/country.json");

    if (country.fail()) {
        cerr << "Falied to open country.json\n";
    }

    country >> countryData;
    country.close();

    for (int i = 0; i < 64; i++) {
        Land *regis = new Land(countryData[to_string(i)]["type"].get<int>(), i,
                               countryData[to_string(i)]["name"].get<string>(),
                               countryData[to_string(i)]["value"].get<int>(),
                               countryData[to_string(i)]["translation"].get<string>());
        regis->setLevel(0);
        // landNameToPos[regis->getName()] = i;
        processMap.push_back(regis);
    }

    nlohmann::json playerData;
    ifstream player;
    player.open("json/config.json");

    if (player.fail()) {
        cerr << "Falied to open config.json\n";
    }

    player >> playerData;
    player.close();

    for (int i = 0; i < 4; i++) {
        vector<int> ownCardFromConfig;
        string strOwnCardFromConfig = playerData[to_string(i)]["ownCard"].get<string>();
        stringstream ss(strOwnCardFromConfig);
        while (ss >> strOwnCardFromConfig) {
            ownCardFromConfig.push_back(stoi(strOwnCardFromConfig));
        }
        cout << "ownCardFromConfig: ";
        for (auto x: ownCardFromConfig) {
            cout << x << " ";
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

    processMap[13]->setOwner(1);
    processMap[13]->setLevel(4);
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);

    // for (int i = 0; i < 5; i++) {
    //     processPlayer[0]->addOwnCards(i);
    // }

    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
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

void eventHandler::moveEntryPoint(int _moveDistance) {
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    buttonState = true;
    emit EnableChanged();
    movePointAnimator(_moveDistance);
}

void eventHandler::commendEntryPoint(QString _instruct) {
    string strInstruct = _instruct.toStdString();
    nlohmann::json commandData;
    ifstream command;
    command.open("json/command.json");

    if (command.fail()) {
        cerr << "Falied to open command.json\n";
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
                } else if (inputCommand == "to") {
                    ss >> inputCommand;
                    if (checkNum(inputCommand) && stoi(inputCommand) <= 64) {
                        int newPos = stoi(inputCommand) % 64;
                        processPlayer[turn]->setPos(newPos);
                        regex r(R"(\{location\})");
                        prompt = regex_replace(prompt, r, to_string(newPos));
                        cerr << prompt << '\n';
                    } else {
                        cerr << "Valid input!\n";
                        break;
                    }
                } else {
                    cerr << "Valid input!\n";
                    break;
                }
            } else if (inputCommand == "/give") {
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
                    cerr << "Valid input!\n";
                    break;
                }

                regex r1(R"(\{playerName\})");
                prompt = regex_replace(prompt, r1, payee);

                ss >> inputCommand;
                int deltaMoney = stoi(inputCommand);
                regex r2(R"(\{money\})");
                prompt = regex_replace(prompt, r2, to_string(deltaMoney));

                if (processPlayer[turn]->getMoney() < deltaMoney) {
                    cerr << "Valid input!\n";
                    break;
                }

                processPlayer[turn]->subMoney(deltaMoney);
                processPlayer[playerNameToID[payee]]->addMoney(deltaMoney);
                cerr << prompt << '\n';
            } else if (inputCommand == "/get") {
                prompt = commandData["get"]["prompt"].get<string>();
                ss >> inputCommand;
                if (checkNum(inputCommand)) {
                    int deltaMoney = stoi(inputCommand);
                    regex r1(R"(\{playerName\})");
                    prompt = regex_replace(prompt, r1, processPlayer[turn]->getPlayerName());
                    regex r2(R"(\{money\})");
                    prompt = regex_replace(prompt, r2, to_string(deltaMoney));
                    cerr << prompt << '\n';
                } else {
                    cerr << "Valid input!\n";
                    break;
                }
            }
            // else if (inputCommand == "/card") {
            //     prompt = commandData["card"]["prompt"].get<string>();
            //     ss >> inputCommand;
            //     processPlayer[turn]->addOwnCards(inputCommand);
            //     regex r(R"(\{card_name\})");
            //     prompt = regex_replace(prompt, r, inputCommand);
            //     cerr << prompt << '\n';
            // }
            else if (inputCommand == "/minigame") {
                prompt = commandData["minigame"]["prompt"].get<string>();
                cerr << prompt << '\n';
                ss >> inputCommand;
                // runMinigame();
            } else if (inputCommand == "/gamestate") {
                prompt = commandData["gamestate"]["prompt"].get<string>();
                ss >> inputCommand;
                if (inputCommand == "INIT") {
                    // initialize();
                } else if (inputCommand == "START") {
                    // start();
                } else if (inputCommand == "MOVED") {
                    // moved();
                } else if (inputCommand == "FINISH") {
                    // finish();
                }
                regex r(R"(\{state\})");
                prompt = regex_replace(prompt, r, inputCommand);
                cerr << prompt << '\n';
            } else if (inputCommand == "/info") {
                cerr << commandData["info"]["prompt"].get<string>();
                // printAllPlayerInfo();
            } else if (inputCommand == "/refresh") {
                cerr << commandData["refresh"]["prompt"].get<string>();
                // refresh();
            } else if (inputCommand == "/list" || inputCommand == "/help") {
                bool a = false;
                if (ss >> inputCommand) {
                    if (inputCommand == "-a") {
                        a = true;
                    }
                }
                for (auto x: commandData) {
                    if (x["name"].get<string>() != "") {
                        cerr << x["name"].get<string>() << " - " << x["description"].get<string>() << '\n';

                        if (a) {
                            cerr << "\tUsage:\t" << x["usage"].get<string>() << '\n';
                            cerr << "\tExamples:\n";
                            for (auto ex: x["examples"]) {
                                cerr << "\t\t" << ex.get<string>() << '\n';
                            }
                        }
                        cerr << '\n';
                    }
                }
            } else {
                cerr << commandData["invalid_command"]["prompt"].get<string>() << '\n';
            }
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

bool eventHandler::skipEntryPoint() {
    ++turn > 3 ? turn = 0 : 0;
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
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
    operateMovePoint.initializeMovePoint(posX, posY, turn);
    emit movePointInitialize();
    std::thread t(&eventHandler::animationThread, this, _step, playerPos, index);
    t.detach();
}

void eventHandler::animationThread(int _times, int _playerPos, int _index) {
    QMetaObject::invokeMethod(&operateMovePoint, "setIsvisable", Qt::QueuedConnection,Q_ARG(bool, true));

    bool origin = false;

    for (int i = 0; i < _times; i++) {
        if (processMap[_playerPos]->getState() == 1 || processPlayer[turn]->getState() == 1) break;

        this_thread::sleep_for(chrono::milliseconds(350));

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
        // 原點處理
        if (origin && _playerPos == 0) {
            processPlayer[turn]->addMoney(8000);
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
        } else if (origin) {
            processPlayer[turn]->addMoney(4000);
            m_displayState->initialStateDisplay(turn, processPlayer[turn]);
        }

        // 解除路障
        if (processMap[_playerPos]->getState() == 1) processMap[_playerPos]->setState(0);
        QMetaObject::invokeMethod(this, "movePointStartMove", Qt::QueuedConnection);
    }
    // 確認是地區收費
    if (processMap[processPlayer[turn]->getPos()]->getType() == 0)toll();

    // 不同type
    if (processMap[processPlayer[turn]->getPos()]->getType() == 1) {
        buttonState = false;
        QMetaObject::invokeMethod(this, "EnableChanged", Qt::QueuedConnection);
        //=================往後加=================
    } else if (processMap[processPlayer[turn]->getPos()]->getType() == 2) {
        // 商店
        emit openShopPopup();
    }

    if (processMap[processPlayer[turn]->getPos()]->getType() != 0) {
        buttonState = false;
        emit skipTurn();
        emit EnableChanged();
    }


    this_thread::sleep_for(chrono::milliseconds(250));
    mapUpdate(landCoordinate, m_mapList, processMap, processPlayer);
    QMetaObject::invokeMethod(&operateMovePoint, "hiddingMovePoint", Qt::QueuedConnection);
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
}


QList<QObject *> eventHandler::mapList() const {
    return m_mapList;
}

void eventHandler::setMapList(const QList<QObject *> &newMapList) {
    if (m_mapList == newMapList)
        return;
    m_mapList = newMapList;
    emit mapListChanged();
}


MovePoint *eventHandler::movePoint() const {
    return m_movePoint;
}

void eventHandler::setMovePoint(MovePoint *newMovePoint) {
    if (m_movePoint == newMovePoint)
        return;
    m_movePoint = newMovePoint;
    emit movePointChanged();
}


StateDisplay *eventHandler::displayState() const {
    return m_displayState;
}

void eventHandler::setDisplayState(StateDisplay *newDisplayState) {
    if (m_displayState == newDisplayState)
        return;
    m_displayState = newDisplayState;
    emit displayStateChanged();
}

UseCardSetting *eventHandler::useCard() const {
    return m_useCard;
}

void eventHandler::setUseCard(UseCardSetting *newUseCard) {
    if (m_useCard == newUseCard)
        return;
    m_useCard = newUseCard;
    emit useCardChanged();
}

bool eventHandler::returnEnableButton() const {
    return buttonState;
}

void eventHandler::toll() {
    int nowPos = processPlayer[turn]->getPos();
    int landOwner = processMap[nowPos]->getOwner();
    if (landOwner != 0 && landOwner != turn + 1 && processMap[nowPos]->getType() == 0) {
        int landValue = processMap[nowPos]->getValue();
        int nowLevel = processMap[nowPos]->getLevel();
        int fee = (nowLevel) * (landValue / 10);
        processPlayer[turn]->subMoney(fee);
        processPlayer[landOwner - 1]->addMoney(fee);
    }
    m_displayState->initialStateDisplay(turn, processPlayer[turn]);
    m_useCard->initialUseCardPopUp(turn, processMap, processPlayer);
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
