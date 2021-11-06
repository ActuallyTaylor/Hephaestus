/*
    Window.cpp
    Zachary lineman
    11/1/21

    =================
    DESCRIPTION
    =================
*/
#include "Window.hpp"

Window* self;

Window::Window() { }

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

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowCallback);
}

void Window::windowLoop() {
    _init();
    glEnable(GL_DEPTH_TEST);
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    self = this;
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        nbFrames ++;

//        if(currentTime - lastTime >= 1.0) {
//            printf("======\n");
//            printf("%f ms/frame\n", 1000.0/double(nbFrames));
//            printf("%d frames per second\n", nbFrames);
//            nbFrames = 0;
//            lastTime += 1.0;
//        }

        _update();
        _render();

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
}

void Window::_init() {
    if (init != nullptr) {
        init();
    }
}

void Window::_destroy() {
    if (destroy != nullptr) {
        destroy();
    }
    glfwTerminate();
}

void Window::_tick() {
    if (tick != nullptr) {
        tick();
    }
}

void Window::_update() {
    if (update != nullptr) {
        update();
    }
}

void Window::_render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw all of the sprites onto screen.
    for(Sprite & sprite : sprites) {
        sprite.draw();
    }

    if (render != nullptr) {
        render();
    }
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        self->controlManager.executeKeybinds(key, action);
    }
}

void Window::windowCallback(GLFWwindow *window, int width, int height) {
    self->width = width;
    self->height = height;
    for (Sprite &sprite: self->sprites) {
        sprite.updateScreenDimensions(width, height);
    }
}

Sprite* Window::addSprite(Sprite sprite) {
    sprite.updateScreenDimensions(width, height);
    sprites.push_back(sprite);
    return &sprites.back();
}

void Window::addKeybind(Keybind keybind) {
    controlManager.addKeybind(keybind);
}
