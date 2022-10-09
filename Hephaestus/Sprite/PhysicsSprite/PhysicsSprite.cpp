/*
    PhysicsSprite.cpp
    Zachary lineman
    11/13/21
    
    =================
    DESCRIPTION
    =================
*/

#include "PhysicsSprite.hpp"

Sprite::Shape PhysicsSprite::getShape() {
    return this->spriteShape;
}

void PhysicsSprite::move(float deltaTime) {
    position += velocity * deltaTime;
    lastVelocity = velocity;
}

void PhysicsSprite::boundSprite() {
    if (position.x  < 0.0f) {
        position.x = 0;
        velocity.x = (-velocity.x * restitution);
    } else if (position.x + dimensions.x > screenSize.x - 0) {
        position.x = screenSize.x - dimensions.x - 1;
        velocity.x = (-velocity.x * restitution);
    }

    if (position.y < 0) {
        position.y = 0;
        velocity.y = (-velocity.y * restitution);
    } else if (position.y + dimensions.y > screenSize.y - 0) {
        position.y = screenSize.y - dimensions.y - 1;
        velocity.y = (-velocity.y * restitution);
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

void PhysicsSprite::addForce(glm::vec3 _velocity) {
    velocity += _velocity;
}

bool PhysicsSprite::physicscCollidable() {
    return true;
}

bool PhysicsSprite::canMovePhysically() {
    return true;
}