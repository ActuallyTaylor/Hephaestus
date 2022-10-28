/*
    PhysicsCollision.cpp
    Zachary lineman
    11/16/21
    
    =================
    DESCRIPTION
    =================
*/

#include <Hephaestus/Collision/PhysicsCollision.hpp>
#include <Hephaestus/Sprite/PhysicsSprite.hpp>

PhysicsCollision::PhysicsCollision(bool success, Sprite* one, Sprite* two, glm::vec3 delta, glm::vec3 penetration) {
    this->successful = success;
    this->one = one;
    this->two = two;
    this->penetration = penetration;
    this->delta = delta;
}

void PhysicsCollision::perform(float deltaTime) {
    auto* pOne = dynamic_cast<PhysicsSprite *>(this->one);
    auto* pTwo = dynamic_cast<PhysicsSprite *>(this->two);
    if (pOne != nullptr && pTwo != nullptr) {
        // Normalized vector of the difference between the pTwo positions
        this->normal = glm::normalize(delta);

        float m1 = pOne->getMass();
        float m2 = pTwo->getMass();

        glm::vec3 v1 = pOne->getVelocity();
        glm::vec3 v2 = pTwo->getVelocity();

        glm::vec3 p1 = pOne->getPosition();
        glm::vec3 p2 = pTwo->getPosition();

        glm::vec3 positionOffset = normal * penetration.x;

        glm::vec3 delt = p1 - p2;
        float dot = glm::dot((v1 - v2), delt);
        float magnitude = (delt.x * delt.x) + (delt.y * delt.y) + (delt.z * delt.z);
//        magnitude *= magnitude;

        float addedMass = m1 + m2;
        glm::vec3 vf1 = v1 - ((2 * m2) / addedMass) * (dot / magnitude) * (delt);

        delt = p2 - p1;
        dot = glm::dot((v2 - v1), delt);
        magnitude = (delt.x * delt.x) + (delt.y * delt.y) + (delt.z * delt.z);
//        magnitude *= magnitude;

        glm::vec3 vf2 = v2 - ((2 * m1 ) / addedMass) * (dot / magnitude) * (delt);

        pOne->position -= positionOffset;
        pTwo->position += positionOffset;

        pOne->velocity = vf1 * PhysicsSprite::restitution;
        pTwo->velocity = vf2 * PhysicsSprite::restitution;

        pOne->boundSprite();
        pTwo->boundSprite();
    } else if (pOne != nullptr) {
        // Two is not a physics sprite but one is.
        handleSolidCollision(two, pOne);
    } else if (pTwo != nullptr) {
        // One is not a physics sprite but two is.
        handleSolidCollision(one, pTwo);
    } else if (pOne == nullptr && pTwo == nullptr) {
        Direction direction = VectorDirection(delta);

        if(direction == UP || direction == DOWN) {
            if(direction == UP) {
                // The non physics sprite is below. This is because the vector from the nps is pointing upwards to the ps.
                one->position.y = two->position.y + two->dimensions.y;
            } else {
                // The non physics sprite is above. This is because the vector from the nps is pointing downwards to the ps.
                one->position.y = two->position.y + one->dimensions.y;

            }
        } else if (direction == LEFT || direction == RIGHT) {
            if(direction == RIGHT) {
                // The non physics sprite is to the right. This is because the vector from the nps is pointing left towards the ps.
                one->position.x = two->position.x - one->dimensions.x;

            } else {
                // The non physics sprite is to the left. This is because the vector from the nps is pointing right towards the ps.
                one->position.x = two->position.x + two->dimensions.x;
            }
        }
    }
}


PhysicsCollision::Direction PhysicsCollision::VectorDirection(glm::vec2 target) {
    glm::vec2 compass[] = {
            glm::vec2(0.0f, 1.0f),	// up
            glm::vec2(1.0f, 0.0f),	// right
            glm::vec2(0.0f, -1.0f),	// down
            glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (PhysicsCollision::Direction)best_match;
}

void PhysicsCollision::handleSolidCollision(Sprite* nonPhysicsSprite, Sprite* _physicsSprite) {
    PhysicsSprite* physicsSprite = dynamic_cast<PhysicsSprite *>(_physicsSprite);
    Direction direction = VectorDirection(delta);

    if(direction == UP || direction == DOWN) {
        physicsSprite->velocity.y = -physicsSprite->velocity.y;
        if(direction == UP) {
            // The non physics sprite is below. This is because the vector from the nps is pointing upwards to the ps.
            physicsSprite->position.y = nonPhysicsSprite->position.y - physicsSprite->dimensions.y;
        } else {
            // The non physics sprite is above. This is because the vector from the nps is pointing downwards to the ps.
            physicsSprite->position.y = nonPhysicsSprite->position.y - nonPhysicsSprite->dimensions.y;
        }
    } else if (direction == LEFT || direction == RIGHT) {
        physicsSprite->velocity.x = -physicsSprite->velocity.x;
        if(direction == RIGHT) {
            // The non physics sprite is to the right. This is because the vector from the nps is pointing left towards the ps.
            physicsSprite->position.x = nonPhysicsSprite->position.x - physicsSprite->dimensions.x;

        } else {
            // The non physics sprite is to the left. This is because the vector from the nps is pointing right towards the ps.
            physicsSprite->position.x = nonPhysicsSprite->position.x - nonPhysicsSprite->dimensions.x;
        }
    }
}