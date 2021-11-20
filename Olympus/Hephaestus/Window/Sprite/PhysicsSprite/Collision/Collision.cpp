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
    if (one != nullptr && two != nullptr) {
        // Normalized vector of the difference between the two positions
        this->normal = glm::normalize(delta);

        float m1 = one->mass;
        float m2 = two->mass;

        glm::vec3 v1 = one->velocity;
        glm::vec3 v2 = two->velocity;

        glm::vec3 p1 = one->position;
        glm::vec3 p2 = two->position;

//        float j = glm::dot(normal, (v2 - v1)) / ((1/ m1) + (1 / m2));
//
//        float magnitude = glm::sqrt(glm::pow(delta.x, 2) + glm::pow(delta.y, 2) + glm::pow(delta.z, 2));
//        glm::vec3 normal = delta / magnitude;
//
//        glm::vec3 vf1 = 1/m1 * (j * normal);
//        glm::vec3 vf2 = - (1/m2 * (j * normal));
//
//        glm::vec3 positionOffset = normal * penetration;
        glm::vec3 delt = p1 - p2;
        float dot = glm::dot((v1 - v2), delt);
        float magnitude = glm::pow(glm::sqrt(glm::pow(delt.x, 2) + glm::pow(delt.y, 2) + glm::pow(delt.z, 2)), 2);

        glm::vec3 vf1 = v1 - ((2 * m2 )/(m1 + m2)) * (dot / magnitude) * (delt);

        delt = p2 - p1;
        dot = glm::dot((v2 - v1), delt);
        magnitude = glm::pow(glm::sqrt(glm::pow(delt.x, 2) + glm::pow(delt.y, 2) + glm::pow(delt.z, 2)), 2);

        glm::vec3 vf2 = v2 - ((2 * m1 )/(m1 + m2)) * (dot / magnitude) * (delt);

//        one->position -= positionOffset;
//        two->position += positionOffset;

        one->velocity = vf1;
        two->velocity = vf2;

        printf("Velocities: %s, %s\n", glm::to_string((m1 * v1) + (m1 * v2)).c_str(), glm::to_string((m1 * vf1) + (m1 * vf2)).c_str());
    } else if (one != nullptr) {

    }
}

/*

        glm::vec3 delt = p1 - p2;
        float dot = glm::dot((v1 - v2), delt);
        float magnitude = glm::sqrt(glm::pow(delt.x, 2) + glm::pow(delt.y, 2) + glm::pow(delt.z, 2));

        glm::vec3 vf1 = v1 - ((2 * m2 )/(m1 + m2)) * (dot / magnitude) * (delt);

        delt = p2 - p1;
        dot = glm::dot((v2 - v1), delt);
        magnitude = glm::sqrt(glm::pow(delt.x, 2) + glm::pow(delt.y, 2) + glm::pow(delt.z, 2));

        glm::vec3 vf2 = v2 - ((2 * m1 )/(m1 + m2)) * (dot / magnitude) * (delt);

 */