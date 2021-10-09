//
//  Window.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Window.hpp"

Window::Window(GLfloat windowWidth, GLfloat windowHeight, char *windowName, GeometryManager &geometryManager, Function windowInit, Function windowDestroy, Function windowTick, Function windowUpdate, Function windowRender) {
    this->init = windowInit;
    this->destroy = windowDestroy;
    this->tick = windowTick;
    this->update = windowUpdate;
    this->render = windowRender;
    this->geometryManager = geometryManager;
    
    // Initialize the library
    if (!glfwInit()) {
        exit(-9);
    }
    
    this->width = windowWidth;
    this->height = windowHeight;

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
    
    glViewport(0, 0, width, height);
    geometryManager.setupShader();
    geometryManager.dimensions = vec2(width, height);
}

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
    render();
}

void Window::windowLoop() {
    _init();
    glEnable(GL_DEPTH_TEST);
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        nbFrames ++;
        
        if(currentTime - lastTime >= 1.0) {
            printf("======\n");
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            printf("%d frames per second\n", nbFrames);
            nbFrames = 0;
            lastTime += 1.0;
        }

        _update();
        _render();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();

    }
}

