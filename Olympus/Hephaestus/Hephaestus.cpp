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

Shader Hephaestus::createShader(std::string vertexPath, std::string fragmentPath) {
    Shader shader = Shader{std::move(vertexPath), std::move(fragmentPath)};
    shader.setup();
    return shader;
}

void Hephaestus::addCamera(Camera *camera) {
    window.addCamera(camera);
}

void Hephaestus::addSprite(Sprite *sprite) {
    window.addSprite(sprite);
}

void Hephaestus::setInit(Function function1) {
    this->window.init = function1;
}

void Hephaestus::setDestroy(Function function1) {
    this->window.destroy = function1;
}

void Hephaestus::setTick(Function function1) {
    this->window.tick = function1;
}

void Hephaestus::setUpdate(Function function1) {
    this->window.update = function1;
}

void Hephaestus::setRender(Function function1) {
    this->window.render = function1;
}

void Hephaestus::addKeybind(int inKeyCode, int inAction, Function inExecutionFunction) {
    Keybind keybind = Keybind{inKeyCode, inAction, inExecutionFunction};
    this->window.addKeybind(keybind);
}

int Hephaestus::getFPS() {
    return this->window.framesPerSecond;
}

int Hephaestus::getNumberOfSprites() {
    return this->window.sprites.size();
}

void Hephaestus::addText(Text* text) {
    this->window.addText(text);
}

void Hephaestus::loadFont(std::string fontPath) {
    this->window.loadFont(fontPath);
}
