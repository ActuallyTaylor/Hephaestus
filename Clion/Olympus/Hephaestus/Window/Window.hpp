//
// Created by Zachary lineman on 11/1/21.
//

#ifndef OLYMPUS_WINDOW_HPP
#define OLYMPUS_WINDOW_HPP
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++ Classes
#include <string>
#include <vector>

class Window {
private:
    std::string windowName;
    int width {720};
    int height { 720 };

    GLFWwindow *window;
public:
    Window(std::string windowName, int width, int height);

    void windowLoop();
};

#endif //OLYMPUS_WINDOW_HPP
