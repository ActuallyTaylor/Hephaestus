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

#include "Triangle.hpp"
#include "Cube.hpp"
#include "Vector3.hpp"
#include "CompressedData.hpp"

using namespace std;

class GeometryManager {
    
public:
    GeometryManager ();
    vector<Triangle> triangles = {};
    vector<Cube> cubes = {};

    // Function for creating vbo, and ebo
    void createVirtualBufferObject();
    
    // Load textures
    void loadTextureAtlas(string atlasPath);
    
    // Functions for adding different shapes
    void addTriangle(Vertex vertices[3]);
    void addCube(Vertex vertices[36]);

    // Draw contents onto the screen
    void draw();
    
    // Clear the screen
    void clear();
    
    GLuint VBO, VAO, EBO, texture;

    GLint indiceCount;

private:
    // Functions that handle organizing all the vertexes
    CompressedData compressTriangleVertices();
};

#endif /* GeometryManager_hpp */
