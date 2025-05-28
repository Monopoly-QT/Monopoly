#include "UseCardSetting.h"
#include <map>
#include <iostream>

UseCardSetting::UseCardSetting(){
    for(int i = 0 ; i < 5 ; i++){
        m_ownCardCount.append(0);
        m_cardUseAvailable.append(0);
    }
    for(int i = 0 ; i < 4 ; i++){
        m_displayTargetPlayer.append(0);
    }
}

void UseCardSetting::initialUseCardPopUp(int _turn,vector<Land*> _land,vector<Player*> _player){
    m_displayTargetLand.clear();
    m_displayAllLand.clear();
    vector<int> ownCard = _player[_turn]->getOwnCards();
    cout<<"ownCard"<<endl;
    for (auto i : ownCard) {
        cout<<i<<" ";
    }
    map<int,int> cardCount;

    for(int i=0 ; i < 5 ; i++){
        cardCount[i] = 0;
    }

    for(int i = 0 ; i < 4 ; i++){
        if(_turn != i && _player[i]->getState() != 1){
            m_displayTargetPlayer[i] = 1;
        }
        else{
            m_displayTargetPlayer[i] = 0;
        }
    }

    cout<<"displayTargetPlayer"<<endl;
    for(int i=0;i<4;i++){
        cout<<m_displayTargetPlayer[i]<<" ";
    }
    cout<<endl;

    for(int i = 0 ; i < 64 ; i++){
        if(_land[i]->getOwner() != _turn && _land[i]->getType() == 0 && _land[i]->getLevel() != 0){
            m_displayTargetLand.append(QString::fromStdString(_land[i]->getName()));
        }
        if(_land[i]->getState() != 1){
            m_displayAllLand.append(QString::fromStdString(to_string(i)+". "+_land[i]->getName()));
        }
    }

    for(auto i :ownCard){
        cardCount[i]++;
    }

    for(int i=0 ; i < 5 ; i++){
        m_ownCardCount[i] = cardCount[i];
        if(cardCount[i] > 0)
            m_cardUseAvailable[i] = 1;
        else
            m_cardUseAvailable[i] = 0;
    }

    emit displayTargetLandChanged();
    emit displayTargetPlayerChanged();
    emit cardUseAvailableChanged();
    emit ownCardCountChanged();
    emit displayAllLandChanged();
    cout<<"ownCardCount"<<endl;
    for(int i=0;i<5;i++){
        cout<<m_ownCardCount[i]<<" ";
    }
    cout<<endl;

    cout<<"cardUseAvailable"<<endl;
    for(int i=0;i<5;i++){
        cout<<m_cardUseAvailable[i]<<" ";
    }
    cout<<endl;
}


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

QList<QString> UseCardSetting::displayAllLand() const
{
    return m_displayAllLand;
}

void UseCardSetting::setDisplayAllLand(const QList<QString> &newDisplayAllLand)
{
    if (m_displayAllLand == newDisplayAllLand)
        return;
    m_displayAllLand = newDisplayAllLand;
    emit displayAllLandChanged();
}
