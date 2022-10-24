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

#include "Sprite.hpp"
#include <Hephaestus/Collision/PhysicsCollision.hpp>
#include <Hephaestus/Shader/Shader.hpp>

class PhysicsSprite: public Sprite {
protected:
    Shape spriteShape = sphere;

    bool effectedByGravity { true };
public:
    glm::vec3 gravitationalAcceleration { 0.0, -9.8, 0.0 };
    constexpr const static float restitution = 0.7;

    using Sprite::Sprite;
    glm::vec3 velocity { 0.0, 0.0, 0.0 };
    glm::vec3 lastVelocity { 0.0, 0.0, 0.0 };

    // Override Functions
    void move(float deltaTime) override;
    void boundSprite();
    Sprite::Shape getShape() override;

    // Getters & Setters
    void setVelocity(glm::vec3 inVelocity);
    glm::vec3 getVelocity();

    void setXVelocity(float x);
    void setYVelocity(float y);
    void setZVelocity(float z);

    void setMass(float inMass);
    void addForce(glm::vec3 force);
    float getMass();

    bool physicscCollidable() override;

    bool canMovePhysically() override;

    float mass { 1.0f };
};


#endif //OLYMPUS_PHYSICSSPRITE_HPP
