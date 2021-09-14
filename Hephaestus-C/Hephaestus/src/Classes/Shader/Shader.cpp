//
//  Shader.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Shader.hpp"

Shader::Shader(char* vertexShader, char* fragmentShader) {
    // Build Shaders
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
}

void Shader::setup() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    
    // Combine into a GPU shader program
    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
}
