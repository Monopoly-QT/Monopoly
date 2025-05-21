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
    player->addMoney(-MEDICAL_EXPENSES * day);
    dayInHospital[player] = day;
}

void Hospital::leaveHospital(Player* player) {
    player->addMoney(MEDICAL_EXPENSES * dayInHospital[player]);
    dayInHospital[player] = 0;
}

int Hospital::getDayInHospital(Player* player) {
    return dayInHospital[player];
}

void Hospital::update() {
    for (auto& [player, day] : dayInHospital) {
        if (day > 0) {
            day--;
        }
    }
}
