#include "../Land/Land.h"
#include "map.h"
#include <iostream>
#include <string>
#include <QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include <QColor>
#include <QString>


using namespace std;

Map::Map(bool _isDisplay,string _order,string _name,string _translation,vector<int> _playerStay,Land* _land){
    m_isDisplay = _isDisplay;
    m_order = QString::fromStdString(_order);
    m_name = QString::fromStdString(_name);
    m_translation = QString::fromStdString(_translation);
    m_isDisplayBuilding.resize(4);
    m_playerStay.resize(4);
    byPlayoerPosSetVisibility(_playerStay ,stoi(_order));
    byLevelSetBuildingVisibility(_land->getLevel());
    byTypeOrOwnerSetColor(_land->getType() , _land->getOwner());
    setIsRoadBlock(false);
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
        if(owner == -1){
            m_displayColor = "#454545";  // 深灰
        }
        else if(owner == 0){
            m_displayColor = "#990000";  // 深紅
        }
        else if(owner == 1){
            m_displayColor = "#005999";  // 深藍
        }
        else if(owner == 2){
            m_displayColor = "#007f00";  // 深綠
        }
        else{
            m_displayColor = "#996600";  // 深黃褐
        }
    }
    else if(type == 1){
        m_displayColor = "#6a1b9a";  // 深紫
    }
    else if(type == 2){
        m_displayColor = "#e65100";  // 深橘
    }
    else{
        m_displayColor = "#00838f";  // 深青
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

bool Map::showTranslation() const {
    return m_showTranslation;
}

void Map::setShowTranslation(bool newShowTranslation) {
    if (m_showTranslation == newShowTranslation)
        return;
    m_showTranslation = newShowTranslation;
    emit showTranslationChanged();
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

QString Map::translation() const
{
    return m_translation;
}

void Map::setTranslation(const QString &newTranslation)
{
    if (m_translation == newTranslation)
        return;
    m_translation = newTranslation;
    emit translationChanged();
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

bool Map::isRoadBlock() const
{
    return m_isRoadBlock;
}

void Map::setIsRoadBlock(bool newIsRoadBlock)
{
    if (m_isRoadBlock == newIsRoadBlock)
        return;
    m_isRoadBlock = newIsRoadBlock;
    emit isRoadBlockChanged();
}
