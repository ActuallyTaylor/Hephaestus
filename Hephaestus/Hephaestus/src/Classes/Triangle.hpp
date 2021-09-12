//
//  Triangle.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/11/21.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Triangle {
    GLfloat vertices[9];
public:
    Triangle (GLfloat vertices[9], int vboNumb);
    int id;
    void Draw ();    
};

#endif /* Triangle_hpp */
