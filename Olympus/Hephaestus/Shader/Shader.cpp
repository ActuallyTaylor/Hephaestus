/*
    Shader.cpp
    Zachary lineman
    11/3/21
    
    =================
    DESCRIPTION
    =================
*/

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

    std::ifstream file(vertexPath.c_str());

    cout << std::__fs::filesystem::current_path() << endl;
    if (file) {
//        std::cout << "file exists: " << vertexPath << std::endl;
    }
    else {
        std::cout << "file doesn't exist: " << vertexPath << std::endl;
    }

    std::ifstream file2(fragmentPath.c_str());

    if (file2) {
//        std::cout << "file exists: " << fragmentPath << std::endl;
    }
    else {
        std::cout << "file doesn't exist: " << fragmentPath << std::endl;
    }
}

Shader::Shader(const char * _vertexShader, const char * _fragmentShader) {
    vertexShader = _vertexShader;
    fragmentShader = _fragmentShader;
}

void Shader::setup() {
    isSetup = true;
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
//        std::cout << "Successfully Compiled Vertex Shader" << std::endl;
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
//        std::cout << "Successfully Compiled Fragment Shader" << std::endl;
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
//        std::cout << "Successfully Compiled Shader Program" << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() {
    if(!isSetup) {
        std::cout << "Shader Not Setup" << std::endl;
    }
    glUseProgram(shaderProgram);
}

void Shader::setFloat(const char *name, float value, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setInteger(const char *name, int value, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setVector2f(const char *name, float x, float y, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform2f(glGetUniformLocation(shaderProgram, name), x, y);
}

void Shader::setVector2f(const char *name, const glm::vec2 &value, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform2f(glGetUniformLocation(shaderProgram, name), value.x, value.y);
}

void Shader::setVector3f(const char *name, float x, float y, float z, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform3f(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void Shader::setVector3f(const char *name, const glm::vec3 &value, bool useShader) {
    if (useShader) {
        use();
    }

    glUniform3f(glGetUniformLocation(shaderProgram, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char *name, float x, float y, float z, float w, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform4f(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}

void Shader::setVector4f(const char *name, const glm::vec4 &value, bool useShader) {
    if (useShader) {
        use();
    }
    glUniform4f(glGetUniformLocation(shaderProgram, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char *name, const glm::mat4 &matrix, bool useShader) {
    if (useShader) {
        use();
    }
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, false, glm::value_ptr(matrix));
}

