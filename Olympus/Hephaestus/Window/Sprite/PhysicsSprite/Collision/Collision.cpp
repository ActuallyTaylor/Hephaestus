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

    glm::vec3 p1 = one->position;
    glm::vec3 p2 = two->position;

    float dotProduct = glm::dot(v1 - v2, p1 - p2);
    float lengthS = pow(glm::length(p1 - p2), 2);

    glm::vec3 vf1 = v1 - ( 2 * m2 / m1 + m2 ) * (dotProduct / lengthS ) * ( p1 - p2 );

    dotProduct = glm::dot(v2 - v1, p2 - p1);
    lengthS = pow(glm::length(p2 - p1), 2);
    glm::vec3 vf2 = v2 - ( 2 * m1 / m1 + m2 ) * (dotProduct / lengthS ) * ( p2 - p1 );
    // Take the normal vector and multiply it by the penetration to find the angle that we need to offset the spheres so that they do not collide
    glm::vec3 positionOffset = normal * penetration;

    one->position -= positionOffset;
    two->position += positionOffset;

    one->velocity += vf1 * normal;
    two->velocity += vf2 * normal;
    printf("Velocities: %s, %s\n", glm::to_string(one->getVelocity()).c_str(), glm::to_string(two->getVelocity()).c_str());

}