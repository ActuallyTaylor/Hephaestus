/*
    Collision.hpp
    Zachary lineman
    11/16/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_COLLISION_HPP
#define OLYMPUS_COLLISION_HPP

#include "../Sprite/Sprite.hpp"

struct Collision {
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    Collision(bool success, Sprite *one, Sprite *two, glm::vec3 delta, glm::vec3 penetration);

    Sprite* one;
    Sprite* two;

    bool successful;

    glm::vec3 penetration;

    glm::vec3 delta;
    glm::vec3 normal;

    void perform();

    void handleSolidCollision(Sprite* nonPhysicsSprite, Sprite* physicsSprite);

    Direction VectorDirection(glm::vec2 target);
};


#endif //OLYMPUS_COLLISION_HPP
