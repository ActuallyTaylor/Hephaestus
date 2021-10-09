//
//  Shader.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Shader.hpp"

Shader::Shader() {
    // Build Shaders
    string line,text;
    ifstream in("./shader.frag");
    while(getline(in, line)) {
        text += line + "\n";
    }
    char* c = new char[text.length() + 1];
    strcpy(c, text.c_str());
    vertexShader = c;

    string line2,text2;
    ifstream in2("./shader.vert");
    while(getline(in2, line2)) {
        text2 += line2 + "\n";
    }
    char* c2 = new char[text.length() + 1];
    strcpy(c2, text2.c_str());
    fragmentShader = c2;
}

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
    } else {
        std::cout << "Successfully Compiled Vertex Shader" << std::endl;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Successfully Compiled Fragment Shader" << std::endl;
    }

    // Combine into a GPU shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Successfully Compiled Shader Program" << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
//    
//    const char *vertexShaderSource = "#version 330 core\n"
//        "layout (location = 0) in vec3 aPos;\n"
//        "void main()\n"
//        "{\n"
//        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//        "}\0";
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    const char *fragmentShaderSource = "#version 330 core\n"
//        "out vec4 FragColor;\n"
//        "void main()\n"
//        "{\n"
//        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
//        "}\0";
//
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    shaderProgram = glCreateProgram();
//
//    
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    glUseProgram(shaderProgram);
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);

}

void Shader::use() {
    glUseProgram(shaderProgram);
}
