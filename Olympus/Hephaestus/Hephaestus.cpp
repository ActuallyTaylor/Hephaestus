/*
    Hephaestus.cpp
    Zachary lineman
    11/1/21

    =================
    Implementations for all the Hephaestus.hpp class functions
    =================
*/

#include "Hephaestus.hpp"

Hephaestus::Hephaestus(const std::string name) {
    this->name = name;
    this->window = Window{name, 720, 720};
}

void Hephaestus::startWindowLoop() {
    window.windowLoop();
}

Shader Hephaestus::createShader(std::string identifier, std::string vertexPath, std::string fragmentPath) {
    Shader shader = Shader{identifier, std::move(vertexPath), std::move(fragmentPath)};
    shader.setup();
    return shader;
}

int Hephaestus::getFPS() const {
    return this->window.framesPerSecond;
}

glm::vec2 Hephaestus::getMousePosition() {
    return this->window.getMousePosition();
}

int Hephaestus::windowWidth() const {
    return this->window.width;
}

int Hephaestus::windowHeight() const {
    return this->window.height;
}

void Hephaestus::openScene(Scene *scene) {
    window.openScene(scene);
}
