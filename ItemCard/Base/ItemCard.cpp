//
// Created by Kai Huang on 2025/5/3.
//

#include "ItemCard.h"
#include <string>

std::string ItemCard::getName() {
    return name;
}

std::string ItemCard::getDescription() {
    return description;
}

int ItemCard::getPrice() {
    return price;
}