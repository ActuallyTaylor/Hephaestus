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
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#include "Triangle.hpp"
#include "Cube.hpp"
#include "Vector3.hpp"
#include "CompressedData.hpp"
#include "Shader.hpp"
#include "GeometryBuffer.hpp"

#include "SpriteRenderer.hpp"

using namespace std;
using namespace glm;

class GeometryManager {
    
public:
    GeometryManager ();
    vector<SpriteRenderer> spriteRenderers;
    int height, width;
    
    //Default Shader
    Shader shader = Shader("./resources/shader.vert", "./resources/shader.frag");

    // Create Shapes and Objects
    void addTriangle(Vertex vertices[3]);
    void addCube(Vertex vertices[36]);

    void addSprite(string id, string texturePath, vec2 position, vec2 size = vec2(10.0f, 10.0f), float rotate = 0.0f, vec3 color = vec3(1.0f));

    // Functions for managing state
    void draw();
    void clear();
    void updateBuffer(string id);
};

#endif /* GeometryManager_hpp */
