/*
    Window.cpp
    Zachary lineman
    11/1/21

    =================
    Implementations for all the Window.hpp class functions
    =================
*/
#include "Window.hpp"
#include "../Scene/Scene.hpp"

Window* self;

Window::Window() {
//    textManager = TextManager();
}

Window::Window(std::string sentWindowName, int sentWidth, int sentHeight) {
    // Set unset class variables
    windowName = sentWindowName;
    width = sentWidth;
    height = sentHeight;
    self = this;

    // Initialize GLFW library
    if (!glfwInit()) {
        exit(-9);
    }

    // Set macOS specific flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    // Start GLEW extension handler
    glewInit();

    glViewport(0, 0, width, height);

    // Set GLFW key callbacks
    glfwSetWindowSizeCallback(window, windowCallback);
}

Text renderingText = Text("", "./fonts/SFNSRounded.ttf", glm::vec2(10, 10), glm::vec4(1.0,1.0,1.0,1.0));

void Window::windowLoop() {
    _init();

    double currentTime = glfwGetTime();
    double lastTime = glfwGetTime();
    double lastFrameCountTime = glfwGetTime();

    int framesThisSecond = 0;
    // Uncomment this to delimit framerate. Currently, limited because physics breaks.
//    glfwSwapInterval(0);
    currentScene->addText(&renderingText);
    currentScene->updateSceneDimensions(width, height);

    while (!glfwWindowShouldClose(window)) {
        framesThisSecond ++;

        if(currentTime - lastFrameCountTime >= 1.0) {
            if (printFrames) {
                printf("======\n");
                printf("%f ms/frame\n", 1000.0 / double(framesThisSecond));
                printf("%d frames per second\n", framesThisSecond);
            }
            framesPerSecond = framesThisSecond;
            framesThisSecond = 0;
            lastFrameCountTime += 1.0;
        }

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        currentScene->deltaTime = deltaTime;

        // Call user-defined callback functions
        const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        _tick();
        _update();
        _render();
        const std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        renderingText.text = "Frame Calculations: " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + "mcs = " + std::to_string((end - start) / 1ms) + "ms = " + std::to_string((end - start) / 1s) + "s.";

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
}

void Window::_init() const {
    if (currentScene->init != nullptr) {
        currentScene->init();
    }
}

void Window::_destroy() const {
    if (currentScene->destroy != nullptr) {
        currentScene->destroy();
    }
    glfwTerminate();
}

void Window::_tick() const {
    if (currentScene->tick != nullptr) {
        currentScene->tick();
    }
}

void Window::_update() const {
    // TODO: Some improvments could be made here. Maybe check to see if we even need to call move.
    currentScene->updateScene();
    if (currentScene->update != nullptr) {
        currentScene->update();
    }
}

void Window::_render() const {
    // Clear the screen
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    currentScene->drawScene();

    if (currentScene->render != nullptr) {
        currentScene->render();
    }
    glDisable(GL_BLEND);
}

void Window::windowCallback(GLFWwindow *window, int width, int height) {
    self->width = width;
    self->height = height;
//    glViewport(0, 0, width, height);
//    glOrtho(0.0f, width, height, 0.0f, -1000.0f, 1000.0f );

    self->currentScene->updateSceneDimensions(width, height);
}


void Window::cameraPositionChanged() {

}

void Window::cameraRotationChanged() {

}

void Window::cameraTargetChanged() {

}

glm::vec2 Window::getMousePosition() const {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { xpos, height - ypos };
}

void Window::openScene(Scene *scene) {
    scene->setupScene(window);
    glfwSetKeyCallback(window, scene->keyCallback);
    glfwSetMouseButtonCallback(window, scene->mouseButtonCallback);
    currentScene = scene;
}
