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

void PhysicsSprite::move(float deltaTime) {
//    time += timeStep;//timeStep * (velocity + timeStep * gravitationalAcceleration.y / 2);
    if (effectedByGravity) {
        velocity += (mass * gravitationalAcceleration) * deltaTime;
    }

    position += velocity;

    if (position.x - (size.x / 2) <= 0.0f) {
        printf("Collided With Left Wall!\n");
        velocity.x = -velocity.x;
        position.x = size.x / 2;
    } else if (position.x + (size.x / 2) >= screenSize.x) {
        printf("Collided With Right Wall!\n");
        velocity.x = -velocity.x;
        position.x = screenSize.x - (size.x / 2);
    }

    if (position.y - (size.y / 2) <= 0.0f) {
        printf("Collided With Top Wall!\n");
        velocity.y = -velocity.y;
        position.y = size.y / 2;
    } else if (position.y + (size.y / 2) >= screenSize.y) {
        printf("Collided With Bottom Wall!\n");
        velocity.y = -velocity.y;
        position.y = screenSize.y - (size.y / 2);
    }
}

void PhysicsSprite::setVelocity(glm::vec3 inVelocity) {
    velocity = inVelocity;
}

glm::vec3 PhysicsSprite::getVelocity() {
    return velocity;
}
/*
 * 𝐽= 𝑛⋅(𝑣𝑖−𝑣𝑗) / 1𝑚𝑖+1𝑚𝑗
 */
void PhysicsSprite::collide(PhysicsSprite* sprite, glm::vec3 normal) {
    float m1 = mass;
    float m2 = sprite->mass;

    glm::vec3 u1 = velocity;
    glm::vec3 u2 = sprite->velocity;

    glm::vec3 newVelocity = (((m1 - m2) / (m1 + m2)) * u1) + (((2 * m2) / (m1 + m2)) * u2);
    glm::vec3 otherNewVelocity = (((2 * m1) / (m1 + m2)) * u1) + (((m2 - m1) / (m1 + m2)) * u2);

    velocity = newVelocity;
    sprite->velocity = otherNewVelocity;
    printf("Velocities: %s, %s\n", glm::to_string(getVelocity()).c_str(), glm::to_string(sprite->getVelocity()).c_str());

}
/*
 *
 */
