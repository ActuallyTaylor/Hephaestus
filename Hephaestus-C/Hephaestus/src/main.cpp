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
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Vertex.hpp"

using namespace std;

// Global Geometry Manager
GeometryManager geometryManager = GeometryManager();

//Global Shader
Shader shader = Shader("./resources/shader.vert", "./resources/shader.frag");

static float randomFloat() {
    float low = -1;
    float high = 1;
    return low + static_cast<float>(rand() / static_cast<float>(RAND_MAX/(high-low)));
}

static bool randomYesNo() {
    float low = 0;
    float high = 1;
    return (low + static_cast<float>(rand() / static_cast<float>(RAND_MAX/(high-low)))) > 0.8;
}

void drawRandomTriangle() {
    Vertex secondTrianglePoints[] = {
        Vertex(Vector3(randomFloat(), randomFloat(), randomFloat()), Vector3(1.0, 1.0, 1.0), Vector2(1.0, 1.0)),
        Vertex(Vector3(randomFloat(), randomFloat(), randomFloat()), Vector3(1.0, 1.0, 1.0), Vector2(1.0, 1.0)),
        Vertex(Vector3(randomFloat(), randomFloat(), randomFloat()), Vector3(1.0, 1.0, 1.0), Vector2(1.0, 1.0))
    };
    geometryManager.addTriangle(secondTrianglePoints);
}

void init() {
    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

//    Vector3 firstTrianglePoints[] = {
//        Vector3(-0.5f, 0.5f, 0.0f),
//        Vector3(0.5f, -0.5f,  0.0f),
//        Vector3(-0.5f, -0.5f,  0.0f),
//    };
//    geometryManager.addTriangle(firstTrianglePoints);
//
//    Vector3 secondTrianglePoints[] = {
//        Vector3(-0.5, 0.5f,  0.0f),
//        Vector3(0.5f, 0.5f,  0.0f),
//        Vector3(0.5f, -0.5f,  0.0f),
//    };
//    geometryManager.addTriangle(secondTrianglePoints);
    
    Vertex firstTrianglePoints[] = {
        Vertex(Vector3(-0.5f,  0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(-0.5f, -0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f))
    };
    geometryManager.addTriangle(firstTrianglePoints);
    
    Vertex secondTrianglePoints[] = {
        Vertex(Vector3(-0.5f,  0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(0.5f,  0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f))
    };
    geometryManager.addTriangle(secondTrianglePoints);
}

void destroy() {

}

void tick() {
    
}

void update() {
    geometryManager.createVirtualBufferObject();
}

void render() {
//    if (randomYesNo()) {
//        drawRandomTriangle();
//    }
    glUseProgram(shader.shaderProgram);
    geometryManager.draw();
    
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        drawRandomTriangle();
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        geometryManager.clear();
    }
}

int main(int argc, const char * argv[]) {
    Window mainWindow = Window(1280, 720, "Hephaestus Game Engine", &shader, &geometryManager, init, destroy, tick, update, render);
    
    //Add the key call
    glfwSetKeyCallback(mainWindow.window, key_callback);

    mainWindow.windowLoop();
    
    return 0;
}
