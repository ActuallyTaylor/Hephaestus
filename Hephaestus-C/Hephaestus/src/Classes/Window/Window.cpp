//
//  Window.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Window.hpp"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window(GLfloat windowWidth, GLfloat windowHeight, char* windowName, Shader *shader, GeometryManager *geometryManager, Function windowInit, Function windowDestroy, Function windowTick, Function windowUpdate, Function windowRender) {
    this->init = windowInit;
    this->destroy = windowDestroy;
    this->tick = windowTick;
    this->update = windowUpdate;
    this->render = windowRender;
    
    // Initialize the library
    if (!glfwInit()) {
        exit(-9);
    }
    
    this->width = windowWidth;
    this->height = windowHeight;
    this->shader = shader;

    // macOS specific flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    
    if (!window) {
        glfwTerminate();
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    //Add the key call
    glfwSetKeyCallback(window, key_callback);
    
    shader->setup();
}
//
//void Triangle::Draw() {
//    int vertMax = id * 3;
//    glDrawArrays(GL_TRIANGLES, vertMax - 3, vertMax);
//}

void Window::_init () {
    init();
}

void Window::_destroy () {
    destroy();
    glfwTerminate();
}

void Window::_tick () {
    tick();
}

void Window::_update () {
    update();
}

void Window::_render () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader->shader_programme);
    render();
}

void Window::windowLoop() {
    _init();
    
    while (!glfwWindowShouldClose(window)) {
        _update();
        _render();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();

    }
}
