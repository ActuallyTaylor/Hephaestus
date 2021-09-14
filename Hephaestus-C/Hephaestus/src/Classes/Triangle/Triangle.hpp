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

using namespace std;

class Triangle {
    
public:
    Triangle (GLfloat triangleVertices[9]);
    vector<GLfloat> vertices;
    int vertexAmount ();
private:

};
#endif /* Triangle_hpp */
