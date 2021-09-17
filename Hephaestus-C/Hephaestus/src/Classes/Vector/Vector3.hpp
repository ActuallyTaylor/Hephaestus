//
//  Vector3.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vector3 {
    Vector3(GLfloat x, GLfloat y, GLfloat z);
    GLfloat x, y, z;
    bool operator == (Vector3& rhs);
    bool operator != (Vector3& rhs);
    
    bool operator == (const Vector3& rhs);
    bool operator != (const Vector3& rhs);

};

#endif /* Vector3_hpp */
