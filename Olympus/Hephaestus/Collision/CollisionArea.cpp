/*
    CollisionArea.cpp
    Zachary lineman
    3/30/22
    
    =================
    DESCRIPTION
    =================
*/

#include "CollisionArea.hpp"

CollisionArea::CollisionArea(glm::vec3 position, glm::vec3 dimensions, std::string identifier, Function executeOnCollide, std::vector<std::string> collisionTags) {
    this->position = position;
    this->dimensions = dimensions;
    this->identifier = identifier;
    this->executeOnCollide = executeOnCollide;
    this->collisionTags = collisionTags;
}

bool CollisionArea::overlaps(Sprite *sprite) {
    bool hasSameTag = false;
    for (const std::string& tag: sprite->collisionTags) {
        if (std::count(collisionTags.begin(), collisionTags.end(), tag)) {
            hasSameTag = true;
        }
    }
    if (!hasSameTag) {
        return false;
    }

    return (sprite->getX() <= position.x + dimensions.x && sprite->getX() + sprite->getWidth() >= position.y) &&
    (sprite->getY() <= position.y + dimensions.y && sprite->getY() + sprite->getHeight() >= position.y) &&
    (sprite->getZ() <= position.z && sprite->getZ() + 0 >= position.z);
}