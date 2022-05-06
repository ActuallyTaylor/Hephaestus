/*
    EncounterSpace.hpp
    Zachary lineman
    5/6/22
    
    =================
    DESCRIPTION
    =================
*/
#include <iostream>
#include "../../Olympus/Hephaestus/Sprite/Sprite.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"

#ifndef LOWDATA_ENCOUNTERSPACE_HPP
#define LOWDATA_ENCOUNTERSPACE_HPP

class EncounterSpace;
typedef std::function<void(EncounterSpace* space)> EncounterCallback;


class EncounterSpace {
    glm::vec3 worldPosition = {0,0,0};

    bool overlapped = false;
    void overlapItem(const std::string& spriteID);
    void leaveOverlapItem(const std::string& spriteID);
public:
    enum SpaceType {
        Grass,
        Rock
    };
    EncounterSpace(float encounterChance, SpaceType spaceType, glm::vec3 worldPosition, EncounterCallback spriteOverlapped);
    uint32_t id;
    float encounterChance = 1.0;

    CollisionArea encounterCollision;
    Sprite encounterSprite;
    SpaceType spaceType;

    EncounterCallback spriteOverlapped;
    void setupSprite(Scene* sReference);

    inline bool operator == (const EncounterSpace& rhs) const {
        return id == rhs.id;
    }
};


#endif //LOWDATA_ENCOUNTERSPACE_HPP
