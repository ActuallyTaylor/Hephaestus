//
// Created by Zachary lineman on 11/1/21.
//

#include "Window.hpp"

Window::Window(std::string sentWindowName, int sentWidth, int sentHeight) {
    windowName = sentWindowName;
    width = sentWidth;
    height = sentHeight;

    // Initialize the library
    if (!glfwInit()) {
        exit(-9);
    }

    // macOS specific flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
}

void Window::windowLoop() {
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

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
}
