//
// Created by Kai Huang on 2025/5/3.
//

#ifndef ROCKETCARD_H
#define ROCKETCARD_H
#include "../Base/ItemCard.h"
#include "../../Player/Player.h"
#include "../../Hospital/Hospital.h"

class RocketCard :  public ItemCard{
public:
    RocketCard() {
        name = "Rocket";
        description = "Designate a player to be sent to the hospital for N rounds.";
        price = 800;
    }

    /**
     * 使用
     * @param patient 病人
     * @param rounds 回數
     * @return 成功與否
     */
    static bool use(Player &patient, int rounds) {
        if (rounds < 1 || rounds > 3) {
            return false;
        }
        Hospital::enterHospital(&patient, rounds);
        return true;
    }
};

#endif //ROCKETCARD_H
