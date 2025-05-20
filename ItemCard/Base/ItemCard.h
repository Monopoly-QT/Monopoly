//
// Created by Kai Huang on 2025/5/3.
//

#ifndef ITEMCARD_H
#define ITEMCARD_H
#include <string>

class Player;

class ItemCard {
protected:
    std::string name = "Default";
    std::string description = "Default";
    int price = 0;

public:
    ItemCard() = default;

    std::string getName();

    std::string getDescription();

    int getPrice();
};

#endif //ITEMCARD_H
