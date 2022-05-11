/*
    Item.cpp
    Zachary lineman
    4/20/22
    
    =================
    DESCRIPTION
    =================
*/

#include "Item.hpp"

#include <utility>
#include "../../../Hephaestus/HephaestusUtility.hpp"
#include "../Characters/MainCharacter.hpp"

Item::Item() {
    objectID = generateID();
    itemID = -1;
    name = "null";
}

Item::Item(int itemID, std::string name, float dropRarity) {
    this->objectID = generateID();
    this->itemID = itemID;
    this->name = std::move(name);
    this->dropRarity = dropRarity;
}
