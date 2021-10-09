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

using namespace std;

// Global Geometry Manager
GeometryManager geometryManager = GeometryManager();
Controls controls = Controls();


static float randomFloat() {
    float low = -1;
    float high = 1;
    return low + static_cast<float>(rand() / static_cast<float>(RAND_MAX/(high-low)));
}

//static bool randomYesNo() {
//    float low = 0;
//    float high = 1;
//    return (low + static_cast<float>(rand() / static_cast<float>(RAND_MAX/(high-low)))) > 0.8;
//}

void drawRandomTriangle() {
    Vertex secondTrianglePoints[] = {
        Vertex(glm::vec3(randomFloat(), randomFloat(), randomFloat()), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(randomFloat(), randomFloat(), randomFloat()), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(randomFloat(), randomFloat(), randomFloat()), glm::vec2(1.0, 1.0))
    };
    geometryManager.addTriangle(secondTrianglePoints);
}

void init() {
    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    
    geometryManager.addSprite("First Sprite", "./resources/missing.jpg");

//    geometryManager.addSprite("Second Sprite", "./resources/wall.jpg", vec3(300.0f, 300.0f ,15.0f), vec2(100.0f, 100.0f), vec3(100.0f, 0.0f, 30.0f));
}

void destroy() {

}

void tick() {
    
}

void update() {
//    geometryManager.createVirtualBufferObject();
}

void render() {
//    if (randomYesNo()) {
//     s   drawRandomTriangle();
//    }
    geometryManager.draw();
}

void moveSpriteUp() {
    Sprite& sprite = geometryManager.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    geometryManager.moveSprite("First Sprite",  vec3(position.x, position.y - 1, position.z));
}

void moveSpriteDown() {
    Sprite& sprite = geometryManager.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    geometryManager.moveSprite("First Sprite",  vec3(position.x, position.y + 1, position.z));
}

void moveSpriteRight() {
    Sprite& sprite = geometryManager.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    geometryManager.moveSprite("First Sprite",  vec3(position.x + 1, position.y, position.z));
}

void moveSpriteLeft() {
    Sprite& sprite = geometryManager.getSprite("First Sprite");
    vec3 position = sprite.getPosition();
    geometryManager.moveSprite("First Sprite",  vec3(position.x - 1, position.y, position.z));
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        drawRandomTriangle();
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        geometryManager.clear();
    } else {
        controls.executeKeybinds(key, action);
    }
}

static void windowCallback(GLFWwindow* window, int width, int height) {
    geometryManager.updateDimensions(vec2(width, height));
}

int main(int argc, const char * argv[]) {
    Window mainWindow = Window(720, 720, "Hephaestus Game Engine", geometryManager, init, destroy, tick, update, render);
    
    controls.addKeybind(Keybind(GLFW_KEY_UP, GLFW_PRESS, moveSpriteUp));
    controls.addKeybind(Keybind(GLFW_KEY_UP, GLFW_REPEAT, moveSpriteUp));

    controls.addKeybind(Keybind(GLFW_KEY_DOWN, GLFW_PRESS, moveSpriteDown));
    controls.addKeybind(Keybind(GLFW_KEY_DOWN, GLFW_REPEAT, moveSpriteDown));

    controls.addKeybind(Keybind(GLFW_KEY_RIGHT, GLFW_PRESS, moveSpriteRight));
    controls.addKeybind(Keybind(GLFW_KEY_RIGHT, GLFW_REPEAT, moveSpriteRight));

    controls.addKeybind(Keybind(GLFW_KEY_LEFT, GLFW_PRESS, moveSpriteLeft));
    controls.addKeybind(Keybind(GLFW_KEY_LEFT, GLFW_REPEAT, moveSpriteLeft));

    //Add the key call
    glfwSetKeyCallback(mainWindow.window, key_callback);
    glfwSetWindowSizeCallback(mainWindow.window, windowCallback);

    mainWindow.windowLoop();
    
    return 0;
}
