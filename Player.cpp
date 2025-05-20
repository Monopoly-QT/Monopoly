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

Player::Player(int _playerID, string _playerName) {
    money = 200000;
    playerID = _playerID;
    playerName = _playerName;
    stringstream ss(_playerName);
    ss >> playerLastName;
    ownHousesPos = {};
    ownCard = {};
    pos = 0;
    state = 0; //0:not in hospital 1:in hospital
    stayInHospitalTurn = 0;
    nextRollDicePoint = 0;
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

void Player::addOwnCards(string _addCard) {
    ownCard.push_back(_addCard);
}

void Player::disOwnCards(string _disCards) {
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
    money = _money;
}

void Player::setPos(int _pos) {
    pos = _pos;
}

void Player::setState(int _state) {
    state = _state;
}

void Player::setPlayerName(string _playerName) {
    playerName = _playerName;
}


void Player::setStayInHospitalTurn(int _turn) {
    stayInHospitalTurn = _turn;
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

vector<string> Player::getOwnCards() {
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
    nextRollDicePoint = _nextRollDicePoint;
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
