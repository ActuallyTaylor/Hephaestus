//
//  GeometryManager.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//


#ifndef GeometryManager_hpp
#define GeometryManager_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

#include "Triangle.hpp"
#include "Cube.hpp"
#include "CompressedData.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

using namespace std;
using namespace glm;

class GeometryManager {
    
public:
    GeometryManager ();
    vec2 dimensions = vec2(0.0, 0.0);
    
    vector<Sprite> sprites;
    //Default Shader
    Shader shader = Shader("./resources/shader.vert", "./resources/shader.frag");

    //Update Data
    void updateBuffer(string id);
    void updateDimensions(vec2 dimensions);
    
    //Create Shapes and Objects
    void addTriangle(Vertex vertices[3]);
    void addCube(Vertex vertices[36]);
    void addSquare(Vertex vertices[6]);
    
    //Create Sprite
    void addSprite(string id, string texturePath);
    void addSprite(string id, string texturePath, vec3 position, vec2 size, vec3 rotation);

    //Manage Sprite
    void moveSprite(string id, vec3 position);
    void rotateSprite(string id, vec3 rotation);
    void scaleSprite(string id, vec2 size);
    
    Sprite& getSprite(string id);

    // Functions for managing state
    void draw();
    void clear();
    void setupShader();
    
private:
    int spriteIDNumber = 0;
};

#endif /* GeometryManager_hpp */
