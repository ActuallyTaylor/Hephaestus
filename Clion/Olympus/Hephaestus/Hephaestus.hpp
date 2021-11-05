/*
    Hephaestus.hpp
    Zachary lineman
    11/3/21

    =================
    DESCRIPTION
    =================
*/

#include <iostream>

#ifndef OLYMPUS_HEPHAESTUS_HPP
#define OLYMPUS_HEPHAESTUS_HPP

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++ Classes
#include <string>
#include <vector>

// Custom Classes
#include "Window/Window.hpp"
#include "Shader/Shader.hpp"

class Hephaestus {
private:
    Window window;
    std::string name;

public:
    explicit Hephaestus(std::string name);

    void startWindowLoop();

    Shader createShader(std::string vertexPath, std::string fragmentPath);
    Sprite* createSprite(Shader shader, std::string texturePath,
                         glm::vec3 position = glm::vec3(300.0f, 300.0f, 0.0f),
                         glm::vec2 size = glm::vec2(50.0f, 50.0f),
                         glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));
//    Sprite* createSprite(Shader shader, std::string texturePath, GLfloat x, GLfloat y, GLfloat z);

    // Set Hephaestus Callback Functions
    void setInit(Function function1);
    void setDestroy(Function function1);
    void setTick(Function function1);
    void setUpdate(Function function1);
    void setRender(Function function1);
};

#endif //OLYMPUS_HEPHAESTUS_HPP
