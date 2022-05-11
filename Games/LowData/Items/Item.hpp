/*
    Item.hpp
    Zachary lineman
    4/20/22
    
    =================
    DESCRIPTION
    =================
*/
#include <iostream>
#include <glm/glm.hpp>

#ifndef LOWDATA_ITEM_HPP
#define LOWDATA_ITEM_HPP

class Item {
public:
    int objectID;
    int itemID;
    float dropRarity { 1.0 };
    std::string name;

    Item();
    Item(int itemID, std::string name, float dropRarity);
};


#endif //LOWDATA_ITEM_HPP
