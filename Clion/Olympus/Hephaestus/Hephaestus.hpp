//
// Created by Zachary lineman on 11/1/21.
//

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

class Hephaestus {
private:
    std::vector<Window> windows;
    std::string name;
public:
    Hephaestus(const std::string& name);

    Window createWindow(const std::string& windowName, int width, int height);
};

#endif //OLYMPUS_HEPHAESTUS_HPP
