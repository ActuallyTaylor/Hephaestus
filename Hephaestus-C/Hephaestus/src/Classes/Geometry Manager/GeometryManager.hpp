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

#include "Triangle.hpp"
#include "Vector3.hpp"
#include "CompressedData.hpp"

using namespace std;

class GeometryManager {
    
public:
    GeometryManager ();
    vector<Triangle> triangles = {};

    // Function for creating vbo
    void createVirtualBufferObject();
    
    // Functions for adding different shapes
    void addTriangle(Vector3 vertices[3]);
    
    // Draw contents onto the screen
    void draw();
private:
    // Functions that handle organizing all the vertexes
    CompressedData compressTriangleVertices();
    GLint indiceCount;
};

#endif /* GeometryManager_hpp */
