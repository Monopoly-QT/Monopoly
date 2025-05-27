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

bool eventHandler::diceEnabled() const {
    return m_diceEnabled;
}

void eventHandler::setDiceEnabled(bool newDiceEnabled) {
    if (m_diceEnabled == newDiceEnabled)
        return;
    m_diceEnabled = newDiceEnabled;
    emit diceEnabledChanged();
}

QString eventHandler::displayMessage_buyPopup() const
{
    return m_displayMessage_buyPopup;
}

void eventHandler::setDisplayMessage_buyPopup(const QString &newDisplayMessage_buyPopup)
{
    if (m_displayMessage_buyPopup == newDisplayMessage_buyPopup)
        return;
    m_displayMessage_buyPopup = newDisplayMessage_buyPopup;
    emit displayMessage_buyPopupChanged();
}

QString eventHandler::displayMessage_messagePopup() const
{
    return m_displayMessage_messagePopup;
}

void eventHandler::setDisplayMessage_messagePopup(const QString &newDisplayMessage_messagePopup)
{
    if (m_displayMessage_messagePopup == newDisplayMessage_messagePopup)
        return;
    m_displayMessage_messagePopup = newDisplayMessage_messagePopup;
    emit displayMessage_messagePopupChanged();
}

QString eventHandler::displayMessage_upgradePopup() const
{
    return m_displayMessage_upgradePopup;
}

void eventHandler::setDisplayMessage_upgradePopup(const QString &newDisplayMessage_upgradePopup)
{
    if (m_displayMessage_upgradePopup == newDisplayMessage_upgradePopup)
        return;
    m_displayMessage_upgradePopup = newDisplayMessage_upgradePopup;
    emit displayMessage_upgradePopupChanged();
}

QString eventHandler::displayMessage_endPopup() const
{
    return m_displayMessage_endPopup;
}

void eventHandler::setDisplayMessage_endPopup(const QString &newDisplayMessage_endPopup)
{
    if (m_displayMessage_endPopup == newDisplayMessage_endPopup)
        return;
    m_displayMessage_endPopup = newDisplayMessage_endPopup;
    emit displayMessage_endPopupChanged();
}

QString eventHandler::displayMessage_bankruptcypopUp() const
{
    return m_displayMessage_bankruptcypopUp;
}

void eventHandler::setDisplayMessage_bankruptcypopUp(const QString &newDisplayMessage_bankruptcypopUp)
{
    if (m_displayMessage_bankruptcypopUp == newDisplayMessage_bankruptcypopUp)
        return;
    m_displayMessage_bankruptcypopUp = newDisplayMessage_bankruptcypopUp;
    emit displayMessage_bankruptcypopUpChanged();
}

bool eventHandler::cardEnabled() const
{
    return m_cardEnabled;
}

void eventHandler::setCardEnabled(bool newCardEnabled)
{
    if (m_cardEnabled == newCardEnabled)
        return;
    m_cardEnabled = newCardEnabled;
    emit cardEnabledChanged();
}

bool eventHandler::cheatEnable() const
{
    return m_cheatEnable;
}

void eventHandler::setCheatEnable(bool newCheatEnable)
{
    if (m_cheatEnable == newCheatEnable)
        return;
    m_cheatEnable = newCheatEnable;
    emit cheatEnableChanged();
}
