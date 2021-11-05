//
//  Vector2.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vector2 {
    Vector2();
    Vector2(GLfloat x, GLfloat y);
    GLfloat x, y;
    bool operator == (Vector2& rhs);
    bool operator != (Vector2& rhs);
    
    bool operator == (const Vector2& rhs);
    bool operator != (const Vector2& rhs);

};

#endif /* Vector2_hpp */
