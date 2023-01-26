/*
    CollisionArea.cpp
    Zachary lineman
    3/30/22
    
    =================
    DESCRIPTION
    =================
*/

#include <Hephaestus//Collision/CollisionArea.hpp>

#include <utility>

CollisionArea::CollisionArea(glm::vec3 position, glm::vec3 dimensions, std::string identifier, IDCallback executeOnCollide, IDCallback executeOnLeave) {
    this->position = position;
    this->dimensions = dimensions;
    this->id = std::move(identifier);
    this->executeOnCollide = std::move(executeOnCollide);
    this->executeOnLeave = std::move(executeOnLeave);
}


CollisionArea::CollisionArea() { }

bool CollisionArea::overlaps(Sprite *sprite) {
    bool collide = (sprite->getX() <= position.x + dimensions.x && sprite->getX() + sprite->getWidth() >= position.x) &&
                    (sprite->getY() <= position.y + dimensions.y && sprite->getY() + sprite->getHeight() >= position.y) &&
                    (sprite->getZ() <= position.z && sprite->getZ() + 0 >= position.z);

    if (collide) {
        spritesInsideCollisionArea.push_back(sprite->id);
    } else {
        auto itr = std::find(spritesInsideCollisionArea.begin(), spritesInsideCollisionArea.end(), sprite->id);
        if (itr != spritesInsideCollisionArea.end()) {
            spritesInsideCollisionArea.erase(itr);
            if (executeOnLeave) {
                executeOnLeave(sprite->id);
            }
        }
    }

    return collide;
}
