/*
    PhysicsCollision.hpp
    Zachary lineman
    11/16/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_COLLISION_HPP
#define OLYMPUS_COLLISION_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include "../Sprite/Sprite.hpp"

struct PhysicsCollision {
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    PhysicsCollision(bool success, Sprite *one, Sprite *two, glm::vec3 delta, glm::vec3 penetration);

    Sprite* one;
    Sprite* two;

    bool successful;

    glm::vec3 penetration{};

    glm::vec3 delta{};
    glm::vec3 normal{};

    void perform(float deltaTime);

    void handleSolidCollision(Sprite* nonPhysicsSprite, Sprite* physicsSprite);

    Direction VectorDirection(glm::vec2 target);
};


#endif //OLYMPUS_COLLISION_HPP
