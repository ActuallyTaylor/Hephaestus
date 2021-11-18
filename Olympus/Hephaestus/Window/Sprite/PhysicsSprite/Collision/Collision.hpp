/*
    Collision.hpp
    Zachary lineman
    11/16/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_COLLISION_HPP
#define OLYMPUS_COLLISION_HPP

#include "../../Sprite.hpp"

struct Collision {
    Collision(bool success, Sprite *one, Sprite *two, glm::vec3 delta, float penetration);

    Sprite* one;
    Sprite* two;

    bool successful;

    float penetration;

    glm::vec3 delta;
    glm::vec3 normal;

    void perform();

};


#endif //OLYMPUS_COLLISION_HPP
