//
//  Window.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Window.hpp"

Window::Window() { }

Window::Window(GLfloat windowWidth, GLfloat windowHeight, char *windowName, GeometryManager &geometryManager, WindowDelegate &windowDelegate) {
    this->windowDelegate = &windowDelegate;
    this->geometryManager = &geometryManager;
    
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
    windowDelegate->_init();
}

void Window::_destroy () {
    windowDelegate->_destroy();
    glfwTerminate();
}

void Window::_tick () {
    windowDelegate->_tick();
}

void Window::_update () {
    windowDelegate->_update();
}

void Window::_render () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    geometryManager->draw();
    windowDelegate->_render();
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

