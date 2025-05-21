#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

Player::Player() {
    money = 200000;
    playerID = 0;
    playerName = "";
    playerLastName = "";
    ownHousesPos = {};
    ownCard = {};
    pos = 0;
    state = 0; //0:not in hospital 1:in hospital
    stayInHospitalTurn = 0;
    nextRollDicePoint = 0;
}

Player::Player(int _money, int _playerID, string _playerName, string _playerLastName, vector<int> _ownCard, int _pos, int _state, int _stayInHospitalTurn,int _nextRollDicePoint) {
    money = _money;
    playerID = _playerID;
    playerName = _playerName;
    playerLastName = _playerLastName;
    ownCard = _ownCard;
    pos = _pos;
    state = _state; //0:not in hospital 1:in hospital
    stayInHospitalTurn = _stayInHospitalTurn;
    nextRollDicePoint = _nextRollDicePoint;
}

void Player::addMoney(int _addition) {
    money += _addition;
}

void Player::subMoney(int _subtraction) {
    money -= _subtraction;
}

void Player::addPos(int _deltaPos) {
    pos += _deltaPos;
    pos %= 64;
}

void Player::addOwnImmovables(int _pos) {
    ownHousesPos.push_back(_pos);
}

void Player::addOwnCards(int _addCard) {
    ownCard.push_back(_addCard);
}

void Player::disOwnCards(int _disCards) {
    auto _cardPos = find(ownCard.begin(), ownCard.end(), _disCards);
    if (_cardPos != ownCard.end()) {
        ownCard.erase(_cardPos);
    }
}

void Player::subPos(int _deltaPos) {
    pos += 64;
    pos -= _deltaPos;
    pos %= 64;
}

void Player::setMoney(int _money) {
    if (money != _money) {
        money = _money;
        emit moneyChanged();
    }
}

void Player::setPos(int _pos) {
    if (pos != _pos) {
        pos = _pos;
        emit posChanged();
    }
}

void Player::setState(int _state) {
    if (state != _state) {
        state = _state;
        emit stateChanged();
    }
}

void Player::setPlayerName(string _playerName) {
    if (playerName != _playerName) {
        playerName = _playerName;
        stringstream ss(_playerName);
        ss >> playerLastName;
        emit playerNameChanged();
        emit playerLastNameChanged();
    }
}

void Player::setStayInHospitalTurn(int _turn) {
    if (stayInHospitalTurn != _turn) {
        stayInHospitalTurn = _turn;
        emit stayInHospitalTurnChanged();
    }
}

int Player::getID() {
    return playerID;
}

int Player::getMoney() {
    return money;
}

int Player::getPos() {
    return pos;
}

string Player::getPlayerName() {
    return playerName;
}

string Player::getPlayerLastName() {
    return playerLastName;
}

vector<int> Player::getOwnImmovables() {
    return ownHousesPos;
}

vector<int> Player::getOwnCards() {
    return ownCard;
}

int Player::getState() {
    return state;
}

int Player::GetstayInHospitalTurn() {
    return stayInHospitalTurn;
}

int Player::getNextRollDicePoint() const {
    return nextRollDicePoint;
}

void Player::setNextRollDicePoint(int _nextRollDicePoint) {
    if (nextRollDicePoint != _nextRollDicePoint) {
        nextRollDicePoint = _nextRollDicePoint;
        emit nextRollDicePointChanged();
    }
}

void Player::removeOwnImmovables(int _pos) {
    auto _HousesPos = find(ownHousesPos.begin(), ownHousesPos.end(), _pos);
    if (_HousesPos != ownHousesPos.end()) {
        ownHousesPos.erase(_HousesPos);
    }
}

bool Player::operator<(const Player rhs) const {
    return playerID < rhs.playerID;
}
