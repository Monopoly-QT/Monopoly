//
// Created by Kai Huang on 2025/5/3.
//

#ifndef DICECONTROL_H
#define DICECONTROL_H

#include "../../Player/Player.h"
#include "../Base/ItemCard.h"

class DiceControlCard : public ItemCard {
public:
    DiceControlCard() {
        name = "Dice Control";
        description = "Customize the number of points for the next roll, which must be within the legal range of dice points.";
        price = 500;
    }

    /**
     * 使用
     * @param player 使用玩家
     * @param roll 點數
     * @return 使用成功與否
     */
    static bool use(Player& player,int roll) {
        if (roll < 1 || roll > 6) {
            return false;
        }
        // TODO Move
        player.setNextRollDicePoint(roll);
        return true;
    }
};

#endif //DICECONTROL_H
