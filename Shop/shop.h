#pragma once
#include <QObject>
#include "../Player/Player.h"

class Shop : public QObject
{
    // Q_OBJECT
    // Q_PROPERTY(Player* player READ player WRITE setPlayer NOTIFY playerChanged)

private:
    // Player* m_player = nullptr; // ✅ 成員變數不要跟函數同名

public:
    // explicit Shop(Player* player, QObject* parent = nullptr);
    explicit Shop() = default;

    // Player* player() const { return m_player; }
    // void setPlayer(Player* p);

    Q_INVOKABLE static bool buyItem(Player *player,int price , int itemIndex);

// signals:
//     void playerChanged();
};
