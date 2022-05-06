/*
    DroppedItem.hpp
    Zachary lineman
    4/25/22
    
    =================
    DESCRIPTION
    =================
*/
#include <iostream>
#include <random>
#include "./Item.hpp"
#include "../../Olympus/Hephaestus/Sprite/Sprite.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"
#include "../../Olympus/Hephaestus/Function.hpp"

#ifndef LOWDATA_DROPPEDITEM_HPP
#define LOWDATA_DROPPEDITEM_HPP

// Forward declare dropped item so the typedef knows of it's existence.
class DroppedItem;
typedef std::function<void(Item* item, DroppedItem* droppedItem)> ItemCallback;

class DroppedItem {
    // MARK: Sprite Stuff
    glm::vec3 worldPosition = {0,0,0};
    Item item;

    bool overlapped = false;
    void overlapItem(const std::string& spriteID);
    void leaveOverlapItem(const std::string& spriteID);
public:
    DroppedItem(Item representativeItem, glm::vec3 worldPosition);
    uint32_t id;

    CollisionArea itemCollision;
    Sprite droppedSprite;

    ItemCallback spriteOverlapped;
    bool pickedUP = false;
    void setupSprite(Scene* sReference);

    inline bool operator == (const DroppedItem& rhs) const {
        return id == rhs.id;
    }
};



#endif //LOWDATA_DROPPEDITEM_HPP
