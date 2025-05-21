//
// Created by Kai Huang on 2025/5/4.
//

#ifndef RANDOMEVENTCARD_H
#define RANDOMEVENTCARD_H
#include "../Base/ItemCard.h"

class RandomEventCard: public ItemCard{
    public:
    RandomEventCard() {
        name = "Random Event";
        description = "Trigger Random Events.";
        price = 10000;
    }
    static bool use(Player& player) {
        // TODO 隨機事件
        return true;
    }
};

#endif //RANDOMEVENTCARD_H
