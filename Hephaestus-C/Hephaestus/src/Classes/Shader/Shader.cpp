//
//  Shader.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Shader.hpp"


Shader::Shader(string vertexPath, string fragmentPath) {
    // Build Shaders
    string line,text;
    ifstream in(vertexPath);
    while(getline(in, line)) {
        text += line + "\n";
    }
    vertexShader = text.c_str();

    string line2,text2;
    ifstream in2(fragmentPath);
    while(getline(in2, line2)) {
        text2 += line2 + "\n";
    }
    fragmentShader = text.c_str();
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
