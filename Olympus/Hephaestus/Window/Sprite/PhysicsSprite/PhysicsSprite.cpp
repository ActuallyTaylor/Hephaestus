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
        velocity.x = -velocity.x * 0.065;
        position.x = 0;
    } else if (position.x + size.x >= screenSize.x) {
        velocity.x = -velocity.x * 0.065;
        position.x = screenSize.x - size.x;
    }

    if (position.y <= 0.0f) {
        velocity.y = -velocity.y * 0.065;
        position.y = 0;
    } else if (position.y + size.y >= screenSize.y) {
        velocity.y = -velocity.y * 0.065;
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

void PhysicsSprite::setXVelocity(float x) {
    velocity.x = x;
}

void PhysicsSprite::setYVelocity(float y) {
    velocity.y = y;
}

void PhysicsSprite::setZVelocity(float z) {
    velocity.z = z;
}