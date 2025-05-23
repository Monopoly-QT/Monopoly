#include "eventHandler.h"

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

bool eventHandler::returnEnableButton() const{
    return buttonState;
}