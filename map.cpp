#include "land.h"
#include "map.h"
#include <iostream>
#include <string>
#include <QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include <QColor>
#include <QString>


using namespace std;

Map::Map(bool _isDisplay,string _order,string _name,vector<int> _playerStay,Land* _land){
    m_isDisplay = _isDisplay;
    m_order = QString::fromStdString(_order);
    m_name = QString::fromStdString(_name);
    m_isDisplayBuilding.resize(4);
    m_playerStay.resize(4);
    byPlayoerPosSetVisibility(_playerStay ,stoi(_order));
    byLevelSetBuildingVisibility(_land->getLevel());
    byTypeOrOwnerSetColor(_land->getType() , _land->getOwner());
}

Map::Map(){
    m_isDisplay = false;
}

void Map::byPlayoerPosSetVisibility(vector<int> playerPos ,int order){
    for(int i = 0; i < 4 ; i++){
        if(playerPos[i] == order){
            m_playerStay[i] = 1;
        }
        else{
            m_playerStay[i] = 0;
        }
    }
    emit playerStayChanged();
}

void Map::byLevelSetBuildingVisibility(int level){
    if(level == 0){
        for(int i = 0 ; i < 4 ; i++){
            m_isDisplayBuilding[i] = 0;
        }
    }
    else if(level == 1){
        m_isDisplayBuilding[0] = 1;
        for(int i = 1 ; i < 4 ; i++){
            m_isDisplayBuilding[i] = 0;
        }
    }
    else if(level == 2){
        for(int i = 0 ; i < 2 ; i++){
            m_isDisplayBuilding[i] = 1;
        }
        for(int i = 2 ; i < 4 ; i++){
            m_isDisplayBuilding[i] = 0;
        }
    }
    else if(level == 3){
        for(int i = 0 ; i < 3 ; i++){
            m_isDisplayBuilding[i] = 1;
        }
        m_isDisplayBuilding[3] = 0;
    }
    else{
        for(int i = 0 ; i < 3 ; i++){
            m_isDisplayBuilding[i] = 0;
        }
        m_isDisplayBuilding[3] = 1;
    }
    emit isDisplayBuildingChanged();
}

void Map::byTypeOrOwnerSetColor(int type ,int owner){
    if(type == 0){
        if(owner == 0){
            m_displayColor = "#454545";
        }
        else if(owner == 1){
            m_displayColor = "#ff1700";
        }
        else if(owner == 2){
            m_displayColor = "#009aff";
        }
        else if(owner == 3){
            m_displayColor = "#0fff00";
        }
        else{
            m_displayColor = "#ffcb00";
        }
    }
    else if(type == 1){
        m_displayColor = "#9c27b0";
    }
    else if(type == 2){
        m_displayColor = "#ff9800";
    }
    else{
        m_displayColor = "#00bcd4";
    }
    emit displayColorChanged();
}







bool Map::isDisplay() const
{
    return m_isDisplay;
}

void Map::setIsDisplay(bool newIsDisplay)
{
    if (m_isDisplay == newIsDisplay)
        return;
    m_isDisplay = newIsDisplay;
    emit isDisplayChanged();
}

QString Map::order() const
{
    return m_order;
}

void Map::setOrder(const QString &newOrder)
{
    if (m_order == newOrder)
        return;
    m_order = newOrder;
    emit orderChanged();
}

QString Map::name() const
{
    return m_name;
}

void Map::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QColor Map::displayColor() const
{
    return m_displayColor;
}

void Map::setDisplayColor(const QColor &newDisplayColor)
{
    if (m_displayColor == newDisplayColor)
        return;
    m_displayColor = newDisplayColor;
    emit displayColorChanged();
}

QList<int> Map::playerStay() const
{
    return m_playerStay;
}

void Map::setPlayerStay(const QList<int> &newPlayerStay)
{
    if (m_playerStay == newPlayerStay)
        return;
    m_playerStay = newPlayerStay;
    emit playerStayChanged();
}

QList<int> Map::isDisplayBuilding() const
{
    return m_isDisplayBuilding;
}

void Map::setIsDisplayBuilding(const QList<int> &newIsDisplayBuilding)
{
    if (m_isDisplayBuilding == newIsDisplayBuilding)
        return;
    m_isDisplayBuilding = newIsDisplayBuilding;
    emit isDisplayBuildingChanged();
}
