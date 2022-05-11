/*
    Hephaestus.cpp
    Zachary lineman
    11/1/21

    =================
    Implementations for all the Hephaestus.hpp class functions
    =================
*/

#include "Hephaestus.hpp"
#include <chrono>

Hephaestus* self;

Hephaestus::Hephaestus(const std::string& _name) {
    srand (static_cast <unsigned> (time(nullptr)));

    name = _name;
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
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

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

Hephaestus::Hephaestus(std::string name, int width, int height) {
    srand (static_cast <unsigned> (time(nullptr)));

    this->name = name;
    this->width = width;
    this->height = height;

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
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

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


Shader Hephaestus::createShader(std::string identifier, std::string vertexPath, std::string fragmentPath) {
    Shader shader = Shader{identifier, std::move(vertexPath), std::move(fragmentPath)};
    shader.setup();
    return shader;
}

void Hephaestus::startWindowLoop() {
    if(self->currentScene == nullptr) {
        std::cerr << "No scene set, terminating window loop" << std::endl;
        return;
    }
    _init();

    glfwGetWindowSize(window, &width, &height);

    self->currentScene->updateSceneDimensions(width, height);

    double currentTime = glfwGetTime();
    double lastTime = glfwGetTime();
    double lastFrameCountTime = glfwGetTime();

    int framesThisSecond = 0;
    // Uncomment this to delimit framerate. Currently, limited because physics breaks.
//    glfwSwapInterval(0);
//    currentScene->addText(&renderingText);
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
//        renderingText.text = "Frame Calculations: " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + "mcs = " + std::to_string((end - start) / 1ms) + "ms = " + std::to_string((end - start) / 1s) + "s.";

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
}

void Hephaestus::_init() const {
    if (currentScene->init != nullptr) {
        currentScene->init();
    }
}

void Hephaestus::_destroy() const {
    if (currentScene->destroy != nullptr) {
        currentScene->destroy();
    }
    glfwTerminate();
}

void Hephaestus::_tick() const {
    if (currentScene->tick != nullptr) {
        currentScene->tick();
    }
}

void Hephaestus::_update() const {
    // TODO: Some improvements could be made here. Maybe check to see if we even need to call move.
    currentScene->updateScene();
    if (currentScene->update != nullptr) {
        currentScene->update();
    }
}

void Hephaestus::_render() const {
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

void Hephaestus::windowCallback(GLFWwindow *window, int width, int height) {
    self->width = width;
    self->height = height;

    self->currentScene->updateSceneDimensions(width, height);
}

void Hephaestus::openScene(Scene *scene) {
    currentScene = nullptr;
    scene->setupScene(window);
    scene->updateSceneDimensions(width, height);

    currentScene = scene;
}

int Hephaestus::getFPS() const {
    return framesPerSecond;
}

int Hephaestus::windowWidth() const {
    return width;
}

int Hephaestus::windowHeight() const {
    return height;
}
