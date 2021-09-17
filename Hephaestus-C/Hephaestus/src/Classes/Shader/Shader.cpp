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
    char* c = new char[text.length() + 1];
    strcpy(c, text.c_str());
    vertexShader = c;

    string line2,text2;
    ifstream in2(fragmentPath);
    while(getline(in2, line2)) {
        text2 += line2 + "\n";
    }
    char* c2 = new char[text.length() + 1];
    strcpy(c2, text2.c_str());
    fragmentShader = c2;

}

void Shader::setup() {
    int  success;
    char infoLog[512];

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    
    // Combine into a GPU shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}
