/*
    PhysicsSprite.cpp
    Zachary lineman
    11/13/21
    
    =================
    DESCRIPTION
    =================
*/

#include "PhysicsSprite.hpp"
#include <glm/gtx/string_cast.hpp>

Sprite::Shape PhysicsSprite::getShape() {
    return this->spriteShape;
}

void PhysicsSprite::move(float deltaTime) {
//    time += timeStep;//timeStep * (velocity + timeStep * gravitationalAcceleration.y / 2);
    if (effectedByGravity) {
        velocity += (mass * gravitationalAcceleration) * deltaTime;
    }

    position += velocity;

    if (position.x  <= 0.0f) {
        printf("Collided With Left Wall!\n");
        velocity.x = -velocity.x;
        position.x = 0;
    } else if (position.x + size.x >= screenSize.x) {
        printf("Collided With Right Wall!\n");
        velocity.x = -velocity.x;
        position.x = screenSize.x - size.x;
    }

    if (position.y <= 0.0f) {
        printf("Collided With Top Wall!\n");
        velocity.y = -velocity.y;
        position.y = size.y;
    } else if (position.y + size.y >= screenSize.y) {
        printf("Collided With Bottom Wall!\n");
        velocity.y = -velocity.y;
        position.y = screenSize.y - size.y;
    }
}

void PhysicsSprite::setVelocity(glm::vec3 inVelocity) {
    velocity = inVelocity;
}

glm::vec3 PhysicsSprite::getVelocity() {
    return velocity;
}

void PhysicsSprite::setMass(float inMass) {
    mass = inMass;
}

float PhysicsSprite::getMass() {
    return mass;
}
