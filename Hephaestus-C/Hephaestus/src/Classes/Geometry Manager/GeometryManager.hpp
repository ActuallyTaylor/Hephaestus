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

#include "Triangle.hpp"
#include "Cube.hpp"
#include "Vector3.hpp"
#include "CompressedData.hpp"
#include "Shader.hpp"

using namespace std;
using namespace glm;

class GeometryManager {
    
public:
    GeometryManager (Shader *shader);
    vector<Triangle> triangles = {};
    vector<Cube> cubes = {};
    Shader *shader;

    // Function for creating vbo, and ebo
    void createVirtualBufferObject();
    
    // Load te&xtures
    void loadTextureAtlas(string atlasPath);
    
    // Functions for adding different shapes
    void addTriangle(Vertex vertices[3]);
    void addCube(Vertex vertices[36]);
    
    void renderSprite(string texture, vec2 position, vec2 size, float rotate, vec3 color);

    // Draw contents onto the screen
    void draw();
    
    // Clear the screen
    void clear();
    
    GLuint VBO, VAO, EBO, textureAtlas;

    GLint indiceCount;

private:
    // Functions that handle organizing all the vertexes
    CompressedData compressTriangleVertices();
};

#endif /* GeometryManager_hpp */
