/*
    EncounterSpace.cpp
    Zachary lineman
    5/6/22
    
    =================
    DESCRIPTION
    =================
*/

#include "EncounterSpace.hpp"
#include <Hephaestus/HephaestusUtility.hpp>

EncounterSpace::EncounterSpace(float encounterChance, EncounterSpace::SpaceType spaceType, glm::vec3 worldPosition, EncounterCallback spriteOverlapped) {
    this->spaceType = spaceType;
    this->worldPosition = worldPosition;
    this->spriteOverlapped = spriteOverlapped;
    this->encounterChance = encounterChance;
}

void EncounterSpace::overlapItem(const std::string& spriteID) {
    if (spriteID == "Main Character" && !overlapped) {
        overlapped = true;
        if (spriteOverlapped) {
            if(randomFloat() <= encounterChance) {
                spriteOverlapped(this);
            }
        }
    }
}

void EncounterSpace::leaveOverlapItem(const std::string& spriteID) {
    overlapped = false;
}

void EncounterSpace::setupSprite(Scene* sceneReference) {
    encounterCollision = CollisionArea(worldPosition, {32, 32, 0}, to_string(id), [this](auto && PH1) { overlapItem(std::forward<decltype(PH1)>(PH1)); }, [this](auto && PH1) { leaveOverlapItem(std::forward<decltype(PH1)>(PH1)); });
    encounterSprite = Sprite(to_string(id), "./Hephaestus/null.png", nearest, worldPosition, { 32, 32 });
    encounterSprite.setCollidable(false);
    encounterSprite.immovable = true;

    sceneReference->addSprite(&encounterSprite);
    sceneReference->addCollisionArea(&encounterCollision);
}