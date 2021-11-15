/*
    PhysicsSprite.hpp
    Zachary lineman
    11/13/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_PHYSICSSPRITE_HPP
#define OLYMPUS_PHYSICSSPRITE_HPP

#include "../Sprite.hpp"

class PhysicsSprite: public Sprite {
protected:
    glm::vec3 gravitationalAcceleration { 0.0, 9.8, 0.0 };

public:
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    bool effectedByGravity { false };
    float mass { 1.0f };
    float restitution { 1.0f };

    using Sprite::Sprite;

    void move(float deltaTime) override;

    void collide(PhysicsSprite* sprite, glm::vec3 normal);

    void setVelocity(glm::vec3 inVelocity);
    glm::vec3 getVelocity();

    glm::vec3 velocity { 0.0, 0.0, 0.0 };
};


#endif //OLYMPUS_PHYSICSSPRITE_HPP
