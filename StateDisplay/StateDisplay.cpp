#include "StateDisplay/StateDisplay.h"

void StateDisplay::initialStateDisplay(int _turn, Player* _player){
    if(_turn == 0)
        m_imageSource = "qrc:/images/Chang.png";
    else if(_turn == 1)
        m_imageSource = "qrc:/images/Wu.png";
    else if(_turn == 2)
        m_imageSource = "qrc:/images/Tuan.png";
    else
        m_imageSource = "qrc:/images/Chiang.png";
    m_name = QString::fromStdString(_player->getPlayerName());
    m_ownMoney = _player->getMoney();

    emit imageSourceChanged();
    emit nameChanged();
    emit ownMoneyChanged();
}

QString StateDisplay::imageSource() const
{
    return m_imageSource;
}
void StateDisplay::setImageSource(const QString &newImageSource)
{
    if (m_imageSource == newImageSource)
        return;
    m_imageSource = newImageSource;
    emit imageSourceChanged();
}

QString StateDisplay::name() const
{
    return m_name;
}

void StateDisplay::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int StateDisplay::ownMoney() const
{
    return m_ownMoney;
}

void StateDisplay::setOwnMoney(int newOwnMoney)
{
    if (m_ownMoney == newOwnMoney)
        return;
    m_ownMoney = newOwnMoney;
    emit ownMoneyChanged();
}
