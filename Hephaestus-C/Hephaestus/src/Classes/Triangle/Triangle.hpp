//
//  Triangle.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector3.hpp"

using namespace std;

class Triangle {
    
public:
    Triangle (Vector3 triangleVertices[3]);
    vector<Vector3> vertices;
    int vertexAmount ();
private:

};
#endif /* Triangle_hpp */
