/*
    CollisionArea.hpp
    Zachary lineman
    3/30/22
    
    =================
    DESCRIPTION
    =================
*/

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL

#include "Hephaestus/Function.hpp"
#include "../Sprite/Sprite.hpp"

#ifndef LOWDATA_COLLISIONAREA_HPP
#define LOWDATA_COLLISIONAREA_HPP


class CollisionArea {
public:
    CollisionArea();
    CollisionArea(glm::vec3 position, glm::vec3 dimensions, std::string identifier, IDCallback executeOnCollide, IDCallback executeOnLeave);

    glm::vec3 position { };
    glm::vec3 dimensions { };
    std::string id { };

    std::vector<std::string> spritesInsideCollisionArea { };

    IDCallback executeOnCollide;
    IDCallback executeOnLeave;

    bool overlaps(Sprite* sprite);

};


#endif //LOWDATA_COLLISIONAREA_HPP
