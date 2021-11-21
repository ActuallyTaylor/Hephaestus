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
    PhysicsSprite* pOne = dynamic_cast<PhysicsSprite *>(this->one);
    PhysicsSprite* pTwo = dynamic_cast<PhysicsSprite *>(this->two);
    if (pOne != nullptr && pTwo != nullptr) {
        // Normalized vector of the difference between the pTwo positions
        this->normal = glm::normalize(delta);

        float m1 = pOne->getMass();
        float m2 = pTwo->getMass();

        glm::vec3 v1 = pOne->getVelocity();
        glm::vec3 v2 = pTwo->getVelocity();

        glm::vec3 p1 = pOne->getPosition();
        glm::vec3 p2 = pTwo->getPosition();

        glm::vec3 positionOffset = normal * penetration;

        glm::vec3 delt = p1 - p2;
        float dot = glm::dot((v1 - v2), delt);
        float magnitude = glm::pow(glm::sqrt(glm::pow(delt.x, 2) + glm::pow(delt.y, 2) + glm::pow(delt.z, 2)), 2);

        glm::vec3 vf1 = v1 - ((2 * m2 )/(m1 + m2)) * (dot / magnitude) * (delt);

        delt = p2 - p1;
        dot = glm::dot((v2 - v1), delt);
        magnitude = glm::pow(glm::sqrt(glm::pow(delt.x, 2) + glm::pow(delt.y, 2) + glm::pow(delt.z, 2)), 2);

        glm::vec3 vf2 = v2 - ((2 * m1 )/(m1 + m2)) * (dot / magnitude) * (delt);

        pOne->setPosition(pOne->getPosition() - positionOffset);
        pTwo->setPosition(pTwo->getPosition() + positionOffset);

        pOne->setVelocity(vf1);
        pTwo->setVelocity(vf2);

        printf("Velocities: %s, %s\n", glm::to_string(vf1).c_str(), glm::to_string(vf2).c_str());
    } else if (pOne == nullptr && pTwo != nullptr) {
        // One is not a physics sprite but two is.

    } else if (pOne != nullptr && pTwo == nullptr) {
        // Two is not a physics sprite but one is.

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