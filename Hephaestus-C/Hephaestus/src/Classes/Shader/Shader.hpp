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

using namespace std;

class Shader {
    const char *vertexShader;
    const char *fragmentShader;
    
public:
    Shader (string vertexShader, string fragmentShader);
    GLuint shaderProgram;
    void setup ();
private:

};


#endif /* Shader_hpp */
