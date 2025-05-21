//
// Created by Kai Huang on 2025/5/4.
//

#ifndef ROADBLOCKCARD_H
#define ROADBLOCKCARD_H

#include "../../Land/Land.h"
#include "../Base/ItemCard.h"
#define MAPSIZE 27

class Roadblock : public ItemCard {
public:
    Roadblock() {
        name = "Roadblock";
        description = "Place barriers on the map to block the next player passing by.";
        price = 5000;
    }

    /**
     * 使用
     * @param _pos 放置的位置
     * @return 放置成功與否
     */
    static bool use(Land& _pos) {
        _pos.setState(1);
        return true;
    }
};

#endif //ROADBLOCKCARD_H
