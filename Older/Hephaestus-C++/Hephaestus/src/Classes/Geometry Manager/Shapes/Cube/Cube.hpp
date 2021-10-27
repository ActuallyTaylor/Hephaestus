//
//  Cube.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/18/21.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vertex.hpp"

using namespace std;

class Cube {
    
public:
    Cube (Vertex triangleVertices[36]);
    vector<Vertex> vertices;
    int vertexAmount ();
private:

};

#endif /* Cube_hpp */
