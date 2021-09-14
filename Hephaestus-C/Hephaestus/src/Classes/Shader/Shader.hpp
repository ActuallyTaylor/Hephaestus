//
//  Shader.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Shader {
    char* vertexShader;
    char* fragmentShader;
    
public:
    Shader (char* vertexShader, char* fragmentShader);
    GLuint shader_programme;
    void setup ();
private:

};


#endif /* Shader_hpp */
