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

using namespace std;

class GeometryManager {
    
public:
    GeometryManager ();
    vector<Triangle> triangles = {};
    
    // Function for creating vbo
    int createVirtualBufferObject();
    
    // Functions for adding different shapes
    void addTriangle(GLfloat vertices[9]);
private:
    // Functions that handle organizing all the vertexes
    vector<GLfloat> compressTriangleVertices();
};

#endif /* GeometryManager_hpp */
