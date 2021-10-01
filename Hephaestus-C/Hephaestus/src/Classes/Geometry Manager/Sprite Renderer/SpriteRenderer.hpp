//
//  SpriteRenderer.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/27/21.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "GeometryBuffer.hpp"
#include "Sprite.hpp"

using namespace glm;

class SpriteRenderer {
public:
    SpriteRenderer(Shader shader, int width, int height);
    vector<Sprite> sprites = {};
    
    void registerSprite(string id, string texturePath, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    void drawAllSprites();
    
    GeometryBuffer geometryBuffer;
};
#endif /* SpriteRenderer_hpp */
