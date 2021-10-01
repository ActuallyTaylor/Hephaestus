//
//  Sprite.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/27/21.
//

#ifndef Sprite_hpp
#define Sprite_hpp


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"

using namespace std;
using namespace glm;

class Sprite {
public:
    Sprite(string id, string texturePath, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    string id;
    string texturePath;
    glm::vec2 position;
    glm::vec2 size = glm::vec2(10.0f, 10.0f);
    float rotate = 0.0f;
    glm::vec3 color = glm::vec3(1.0f);
};

#endif /* Sprite_hpp */
