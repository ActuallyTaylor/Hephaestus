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
#include "../../Collision/Collision.hpp"
#include "../../Shader/Shader.hpp"

class PhysicsSprite: public Sprite {
protected:
    glm::vec3 gravitationalAcceleration { 0.0, -9.8, 0.0 };

    Shape spriteShape = sphere;

    glm::vec3 velocity { 0.0, 0.0, 0.0 };

    bool effectedByGravity { true };
    float mass { 1.0f };

public:
    using Sprite::Sprite;

    // Override Functions
    void move(float deltaTime) override;
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

    bool collidable() override;

    bool canMove() override;
};


#endif //OLYMPUS_PHYSICSSPRITE_HPP
