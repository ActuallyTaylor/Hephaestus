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

// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include Classes
#include "Window.hpp"
#include "Shader.hpp"
#include "GeometryManager.hpp"

using namespace std;

char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";


char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
"}";


// Global Geometry Manager
GeometryManager geometryManager = GeometryManager();

//Global Shader
Shader shader = Shader(vertex_shader, fragment_shader);

void init() {
    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    float firstTrianglePoints[] = {
        -0.5,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
    };
    geometryManager.addTriangle(firstTrianglePoints);

    float secondTrianglePoints[] = {
        -0.5, 0.5f,  0.0f,
        0.5f, 0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
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
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(int argc, const char * argv[]) {
    /*
     Define Shaders
     */
    
    Window mainWindow = Window(1280, 720, "Hephaestus Game Engine", &shader, &geometryManager, init, destroy, tick, update, render);
    
    mainWindow.windowLoop();
    return 0;
}
