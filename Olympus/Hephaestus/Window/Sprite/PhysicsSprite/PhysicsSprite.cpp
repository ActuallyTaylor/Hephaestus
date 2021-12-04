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

float friction = 0.1;

Sprite::Shape PhysicsSprite::getShape() {
    return this->spriteShape;
}

void PhysicsSprite::move(double deltaTime) {
    if (effectedByGravity) {
        velocity += (mass * gravitationalAcceleration);
    }

    position += velocity * float(deltaTime);

    if (position.x  < 0.0f) {
        velocity.x = -velocity.x * friction;
        position.x = 0;
    } else if (position.x + size.x > screenSize.x) {
        velocity.x = -velocity.x * friction;
        position.x = screenSize.x - size.x;
    }

    if (position.y < 0.0f) {
        velocity.y = -velocity.y * friction;
        position.y = 0;
    } else if (position.y + size.y > screenSize.y) {
        velocity.y = -velocity.y * friction;
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