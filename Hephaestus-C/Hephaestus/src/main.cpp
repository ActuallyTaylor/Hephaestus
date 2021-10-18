//
//  main.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/9/21.
//

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <functional>

// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include Classes
#include "Window.hpp"
#include "Shader.hpp"
#include "GeometryManager.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Controls.hpp"

#include "Hephaestus.hpp"


using namespace std;

Hephaestus engine = Hephaestus();
//
//static float randomFloat() {
//    float low = -1;
//    float high = 1;
//    return low + static_cast<float>(rand() / static_cast<float>(RAND_MAX/(high-low)));
//}

void init() {
    engine.addSprite("First Sprite", "./resources/missing.jpg");
    engine.addSprite("Second Sprite", "./resources/wall.jpg", vec3(300.0f, 300.0f ,15.0f), vec2(100.0f, 100.0f), vec3(100.0f, 0.0f, 30.0f));
}

void destroy() {
    
}

void tick() {
    
}

void update() {
    
}

void render() {
    
}

void moveSpriteUp() {
    Sprite& sprite = engine.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    engine.moveSprite("First Sprite",  vec3(position.x, position.y - 10, position.z));
}

void moveSpriteDown() {
    Sprite& sprite = engine.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    engine.moveSprite("First Sprite",  vec3(position.x, position.y + 10, position.z));
}

void moveSpriteRight() {
    Sprite& sprite = engine.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    engine.moveSprite("First Sprite",  vec3(position.x + 10, position.y, position.z));
}

void moveSpriteLeft() {
    Sprite& sprite = engine.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    engine.moveSprite("First Sprite",  vec3(position.x - 10, position.y, position.z));
}

int main(int argc, const char * argv[]) {
    WindowDelegate delegate = WindowDelegate();
    delegate.init = init;
    delegate.update = update;
    delegate.destroy = destroy;
    delegate.render = render;
    
    engine.windowDelegate = delegate;
    
    engine.addKeybind(Keybind(GLFW_KEY_UP, GLFW_PRESS, moveSpriteUp));
    engine.addKeybind(Keybind(GLFW_KEY_UP, GLFW_REPEAT, moveSpriteUp));

    engine.addKeybind(Keybind(GLFW_KEY_DOWN, GLFW_PRESS, moveSpriteDown));
    engine.addKeybind(Keybind(GLFW_KEY_DOWN, GLFW_REPEAT, moveSpriteDown));

    engine.addKeybind(Keybind(GLFW_KEY_RIGHT, GLFW_PRESS, moveSpriteRight));
    engine.addKeybind(Keybind(GLFW_KEY_RIGHT, GLFW_REPEAT, moveSpriteRight));

    engine.addKeybind(Keybind(GLFW_KEY_LEFT, GLFW_PRESS, moveSpriteLeft));
    engine.addKeybind(Keybind(GLFW_KEY_LEFT, GLFW_REPEAT, moveSpriteLeft));
    
    engine.startWindowLoop();
    
    return 0;
}
