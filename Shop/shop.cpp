#include "shop.h"

#include "UseCardSetting/UseCardSetting.h"

// Shop::Shop(Player* player, QObject* parent)
//     : QObject(parent), m_player(player) {}
//
// void Shop::setPlayer(Player* p)
// {
//     if (m_player != p) {
//         m_player = p;
//         emit playerChanged();
//     }
// }

bool Shop::buyItem(Player* player,int price , int itemIndex)
{
    if (player->getMoney() < price) return false;
    player->subMoney(price);
    player->addOwnCards(itemIndex);
    cout << "Buy Item: " << itemIndex << endl;
    for (auto i:player->getOwnCards()) {
        cout << i << ' ';
    }
    cout<<endl;
    return true;
}
