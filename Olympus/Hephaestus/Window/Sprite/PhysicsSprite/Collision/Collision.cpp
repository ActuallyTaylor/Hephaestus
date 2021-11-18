/*
    Collision.cpp
    Zachary lineman
    11/16/21
    
    =================
    DESCRIPTION
    =================
*/

#include <glm/gtx/string_cast.hpp>
#include "Collision.hpp"
#include "../PhysicsSprite.hpp"

Collision::Collision(bool success, Sprite* one, Sprite* two, glm::vec3 delta, float penetration) {
    this->successful = success;
    this->one = one;
    this->two = two;
    this->penetration = penetration;
    this->delta = delta;
}

void Collision::perform() {
    PhysicsSprite* one = dynamic_cast<PhysicsSprite *>(this->one);
    PhysicsSprite* two = dynamic_cast<PhysicsSprite *>(this->two);

    // Normalized vector of the difference between the two positions
    this->normal = glm::normalize(delta);

    float m1 = one->mass;
    float m2 = two->mass;

    glm::vec3 v1 = one->velocity;
    glm::vec3 v2 = two->velocity;

    // Take the normal vector and multiply it by the penetration to find the angle that we need to offset the spheres so that they do not collide
    glm::vec3 positionOffset = normal * penetration;

    one->position -= normal * penetration;
    two->position += normal * penetration;

}