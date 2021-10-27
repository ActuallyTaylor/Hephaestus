//
//  Shader.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {
    const char *vertexShader;
    const char *fragmentShader;
    
public:
    Shader ();
    Shader (string vertexShader, string fragmentShader);
    GLuint shaderProgram;
    void setup ();
    void use();
    
    void setFloat (const char *name, float value, bool useShader = false);
    void setInteger (const char *name, int value, bool useShader = false);
    void setVector2f (const char *name, float x, float y, bool useShader = false);
    void setVector2f (const char *name, const glm::vec2 &value, bool useShader = false);
    void setVector3f (const char *name, float x, float y, float z, bool useShader = false);
    void setVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
    void setVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    void setVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
    void setMatrix4 (const char *name, const glm::mat4 &matrix, bool useShader = false);

private:

};


#endif /* Shader_hpp */
