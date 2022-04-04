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

#include "../Function.hpp"
#include "../Sprite/Sprite.hpp"

#ifndef LOWDATA_COLLISIONAREA_HPP
#define LOWDATA_COLLISIONAREA_HPP


class CollisionArea {
public:
    CollisionArea(glm::vec3 position, glm::vec3 dimensions, std::string identifier, Function executeOnCollide, std::vector<std::string> collisionTags);

    glm::vec3 position { };
    glm::vec3 dimensions { };
    std::string identifier { };
    std::vector<std::string> collisionTags { };

    Function executeOnCollide;

    bool overlaps(Sprite* sprite);

};


#endif //LOWDATA_COLLISIONAREA_HPP
