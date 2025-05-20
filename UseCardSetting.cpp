#include "UseCardSetting.h"


QList<int> UseCardSetting::displayTargetPlayer() const
{
    return m_displayTargetPlayer;
}

void UseCardSetting::setDisplayTargetPlayer(const QList<int> &newDisplayTargetPlayer)
{
    if (m_displayTargetPlayer == newDisplayTargetPlayer)
        return;
    m_displayTargetPlayer = newDisplayTargetPlayer;
    emit displayTargetPlayerChanged();
}

QList<QString> UseCardSetting::displayTargetLand() const
{
    return m_displayTargetLand;
}

void UseCardSetting::setDisplayTargetLand(const QList<QString> &newDisplayTargetLand)
{
    if (m_displayTargetLand == newDisplayTargetLand)
        return;
    m_displayTargetLand = newDisplayTargetLand;
    emit displayTargetLandChanged();
}

QList<int> UseCardSetting::cardUseAvailable() const
{
    return m_cardUseAvailable;
}

void UseCardSetting::setCardUseAvailable(const QList<int> &newCardUseAvailable)
{
    if (m_cardUseAvailable == newCardUseAvailable)
        return;
    m_cardUseAvailable = newCardUseAvailable;
    emit cardUseAvailableChanged();
}

QList<int> UseCardSetting::ownCardCount() const
{
    return m_ownCardCount;
}

void UseCardSetting::setOwnCardCount(const QList<int> &newOwnCardCount)
{
    if (m_ownCardCount == newOwnCardCount)
        return;
    m_ownCardCount = newOwnCardCount;
    emit ownCardCountChanged();
}
