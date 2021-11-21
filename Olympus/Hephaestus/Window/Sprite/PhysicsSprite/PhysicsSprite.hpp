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
#include "Collision/Collision.hpp"
#include "../../../Shader/Shader.hpp"

class PhysicsSprite: public Sprite {
protected:
    glm::vec3 gravitationalAcceleration { 0.0, 9.8, 0.0 };

    Shape spriteShape = sphere;

    glm::vec3 velocity { 0.0, 0.0, 0.0 };

    bool effectedByGravity {false  };
    float mass { 1.0f };

public:
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };


    using Sprite::Sprite;

    // Override Functions
    void move(float deltaTime) override;
    Sprite::Shape getShape() override;

    // Getters & Setters
    void setVelocity(glm::vec3 inVelocity);
    glm::vec3 getVelocity();

    void setMass(float inMass);
    float getMass();

};


#endif //OLYMPUS_PHYSICSSPRITE_HPP
