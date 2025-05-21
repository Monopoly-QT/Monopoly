//
// Created by Kai Huang on 2025/5/3.
//

#ifndef DISTROYIMMOVABLECARD_H
#define DISTROYIMMOVABLECARD_H

#include "../../Player/Player.h"
#include "../Base/ItemCard.h"

class DestroyImmovableCard : public ItemCard {
public:
    DestroyImmovableCard() {
        name = "Destroy Immovable";
        description = "Destroy a property of a player.";
        price = 1000;
    }

    /**
     * 使用
     * @param immovableOwner 拆處對象
     * @param housePos 拆除位置
     * @return 拆除成功與否
     */
    static bool use(Player &immovableOwner, int housePos) {
        vector<int> ownersImmovable = immovableOwner.getOwnImmovables();
        if (ranges::find(ownersImmovable, housePos) == ownersImmovable.end()) {
            return false;
        }
        immovableOwner.removeOwnImmovables(housePos);
        return true;
    }
};

#endif //DISTROYIMMOVABLECARD_H
