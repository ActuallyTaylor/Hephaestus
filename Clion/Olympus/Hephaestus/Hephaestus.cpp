/*
    Hephaestus.cpp
    Zachary lineman
    11/1/21

    =================
    DESCRIPTION
    =================
*/

#include "Hephaestus.hpp"

#include <utility>

Hephaestus::Hephaestus(const std::string name) {
    this->name = name;
    this->window = Window{name, 720, 720};
}

void Hephaestus::startWindowLoop() {
    window.windowLoop();
}

Shader Hephaestus::createShader(std::string vertexPath, std::string fragmentPath) {
    return  Shader{std::move(vertexPath), std::move(fragmentPath)};
}

Sprite* Hephaestus::createSprite(Shader shader, std::string texturePath) {
    Sprite sprite = Sprite{shader, std::move(texturePath)};
    sprites.push_back(sprite);
    return &sprites.back();
}

Sprite* Hephaestus::createSprite(Shader shader, std::string texturePath, GLfloat x, GLfloat y, GLfloat z) {
    Sprite sprite = Sprite{shader, std::move(texturePath), x, y, z};
    sprites.push_back(sprite);
    return &sprites.back();
}

void Hephaestus::setInit(Function function1) {
//    this->window
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

