//
//  Hephaestus.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/8/21.
//

#include "Hephaestus.hpp"

GeometryManager* geoManager;
Controls* conManager;

/*
 Initialization Functions
 */
Hephaestus::Hephaestus() {
    char name[] = "Hephaestus Game Engine";
    
    mainWindow = Window(720, 720, name, geometryManager, windowDelegate);
    geoManager = &geometryManager;
    conManager = &controls;
    
    glfwSetKeyCallback(mainWindow.window, keyCallback);
    glfwSetWindowSizeCallback(mainWindow.window, windowCallback);
}

void Hephaestus::startWindowLoop() {
    mainWindow.windowLoop();
}

/*
 OpenGL Callback Functions
 */

void Hephaestus::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        conManager->executeKeybinds(key, action);
    }
}

void Hephaestus::windowCallback(GLFWwindow* window, int width, int height) {
    geoManager->updateDimensions(vec2(width, height));
}

/*
 API Functions
 */

void Hephaestus::addKeybind(Keybind keybind) {
    controls.addKeybind(keybind);
}

void Hephaestus::addSprite(string id, string texturePath) {
    geometryManager.addSprite(id, texturePath);
}

void Hephaestus::addSprite(string id, string texturePath, vec3 position = vec3(1.0f), vec2 size = vec2(1.0f), vec3 rotation =  vec3(1.0f)) {
    geometryManager.addSprite(id, texturePath, position, size, rotation);
}

void Hephaestus::moveSprite(string id, vec3 position) {
    geometryManager.moveSprite(id, position);
}

void Hephaestus::rotateSprite(string id, vec3 rotation) {
    geometryManager.rotateSprite(id, rotation);
}

void Hephaestus::scaleSprite(string id, vec2 size) {
    geometryManager.scaleSprite(id, size);
}

Sprite& Hephaestus::getSprite(string id) {
    return geometryManager.getSprite(id);
}
