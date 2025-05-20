#include "Land.h"
#include<QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include<QColor>

Land::Land() {
    type = 0;   // 0:normal 1:event 2:store 3:hospital 4: Start
    pos = 0;
    owner = 0; //0:null 1:player1 2:player2 3:player3 4:player4
    level = 0; //only for house 0:empty 1:one house 2:two houses 3:three houses 4:motel
    state = 0; //0:normal 1:have roadblocks
    name = "";
    value = 0;
}

Land::Land(int _type, int _pos, string _name, int _value) {
    type = _type;   // 0:normal 1:event 2:store 3:hospital 4: Start
    pos = _pos;
    owner = 0; //0:null 1:player1 2:player2 3:player3 4:player4
    level = 0; //only for house 0:empty 1:one house 2:two houses 3:three houses 4:motel
    state = 0; //0:normal 1:have roadblocks
    name = _name;
    value = _value;
}

void Land::setOwner(int _player) {
    owner = _player;
}

void Land::setType(int _type) {
    type = _type;
}

void Land::setLevel(int _level) {
    level = _level;
}

void Land::setState(int _state) {
    state = _state;
}

string Land::getName() {
    return name;
}

int Land::getType() {
    return type;
}

int Land::getPos() {
    return pos;
}

int Land::getOwner() {
    return owner;
}

int Land::getLevel() {
    return level;
}

int Land::getState() {
    return state;
}

int Land::getValue() {
    return value;
}
