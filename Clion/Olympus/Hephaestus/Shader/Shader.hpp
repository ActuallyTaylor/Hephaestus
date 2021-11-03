/*
    Shader.hpp
    Zachary lineman
    11/3/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_SHADER_HPP
#define OLYMPUS_SHADER_HPP

// iO Streams
#include <iostream>
#include <fstream>
#include <sstream>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {
    const char *vertexShader;
    const char *fragmentShader;

public:
    Shader();
    Shader(string vertexPath, string fragmentPath);
    void setup();
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
    GLuint shaderProgram;

};

#endif //OLYMPUS_SHADER_HPP
