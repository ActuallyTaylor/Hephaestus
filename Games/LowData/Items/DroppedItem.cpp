/*
    DroppedItem.cpp
    Zachary lineman
    4/25/22
    
    =================
    DESCRIPTION
    =================
*/

#include "DroppedItem.hpp"
#include <utility>

DroppedItem::DroppedItem(Item representativeItem, glm::vec3 worldPosition) {
    id = generateID();

    this->item = std::move(representativeItem);
    this->worldPosition = worldPosition;
}

void DroppedItem::setupSprite(Scene* sceneReference) {
    itemCollision = CollisionArea(worldPosition, {24, 24, 0}, item.name, [this](auto && PH1) { overlapItem(std::forward<decltype(PH1)>(PH1)); }, [this](auto && PH1) { leaveOverlapItem(std::forward<decltype(PH1)>(PH1)); });
    std::string itemPath = "./Items/" + item.name + ".png";
    droppedSprite = Sprite(item.name + std::to_string(item.objectID), itemPath, nearest, worldPosition, { 24, 24 });
    droppedSprite.setCollidable(false);
    droppedSprite.immovable = true;

    sceneReference->addSprite(&droppedSprite);
    sceneReference->addCollisionArea(&itemCollision);
}

void DroppedItem::overlapItem(const std::string& spriteID) {
    if (spriteID == "Main Character" && !overlapped) {
        overlapped = true;
        if (spriteOverlapped) {
            cout <<"Overlapped: " << id << endl;
            spriteOverlapped(&item, this);
        }
    }
}

void DroppedItem::leaveOverlapItem(const std::string& spriteID) {
    overlapped = false;
}
