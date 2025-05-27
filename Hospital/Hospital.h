//
// Created by Kai Huang on 2025/5/2.
//

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <map>
#include "../Player/Player.h"

using namespace std;

class Hospital {
private:
    static std::map<Player*, int> dayInHospital; // 每位玩家在醫院中剩餘的天數

    Hospital() = default; // 禁止被實例化

public:
    // 判斷玩家是否在醫院
    static bool isInHospital(Player* player);

    // 把玩家送進醫院
    static void enterHospital(Player* player, int day);

    // 把玩家送出醫院
    static void leaveHospital(Player* player);

    // 取得該玩家剩餘的天數
    static int getDayInHospital(Player* player);

    // 把天數-1
    static void update(Player* player);
};

#endif //HOSPITAL_H
