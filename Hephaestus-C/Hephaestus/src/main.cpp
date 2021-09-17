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

using namespace std;

// Global Geometry Manager
GeometryManager geometryManager = GeometryManager();

//Global Shader
Shader shader = Shader("./resources/shader.vert", "./resources/shader.frag");

void init() {
    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    Vector3 firstTrianglePoints[] = {
        Vector3(-0.5f, 0.5f, 0.0f),
        Vector3(0.5f, -0.5f,  0.0f),
        Vector3(-0.5f, -0.5f,  0.0f),
    };
    geometryManager.addTriangle(firstTrianglePoints);

    Vector3 secondTrianglePoints[] = {
        Vector3(-0.5, 0.5f,  0.0f),
        Vector3(0.5f, 0.5f,  0.0f),
        Vector3(0.5f, -0.5f,  0.0f),
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
    geometryManager.draw();
    
}

int main(int argc, const char * argv[]) {
    Window mainWindow = Window(1280, 720, "Hephaestus Game Engine", &shader, &geometryManager, init, destroy, tick, update, render);
    
    mainWindow.windowLoop();
    return 0;
}
