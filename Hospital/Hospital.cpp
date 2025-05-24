//
// Created by Kai Huang on 2025/5/2.
//
#include "Hospital.h"
#define MEDICAL_EXPENSES 50
#include <map>

std::map<Player*, int> Hospital::dayInHospital;

bool Hospital::isInHospital(Player* player) {
    return dayInHospital[player] != 0;
}

void Hospital::enterHospital(Player* player, int day) {
    player->setState(1);
    player->setPos(32);
    player->subMoney(MEDICAL_EXPENSES * day);
    dayInHospital[player] = (day-1);
}

void Hospital::leaveHospital(Player* player) {
    player->addMoney(MEDICAL_EXPENSES * dayInHospital[player]);
    dayInHospital[player] = 0;
    player->setState(0);
}

int Hospital::getDayInHospital(Player* player) {
    return dayInHospital[player];
}

void Hospital::update() {
    for (auto& [player, day] : dayInHospital) {
        if (day > 0) {
            day--;
        }
        else player->setState(0);
    }
}
