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
#include <strings.h>
#include <vector>

// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include Classes
#include "Window.hpp"
#include "Shader.hpp"

using namespace std;

//int currentTriangleID = 1;
vector<GLfloat> triangleVertices = {};

static void addTriangle(GLfloat (&vertices)[9]) {
    for(int i = 0; i < 9; i++) {
        triangleVertices.push_back(vertices[i]);
    }
}

unsigned long loadVertices() {
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(float), triangleVertices.data(), GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    return triangleVertices.size();
}

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
    addTriangle(firstTrianglePoints);

    float secondTrianglePoints[] = {
        -0.5, 0.5f,  0.0f,
        0.5f, 0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
    };
    addTriangle(secondTrianglePoints);
    
    int verticeCount = loadVertices();
}

void destroy() {
    
}

void tick() {
    
}

void update() {
}

void render() {
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(int argc, const char * argv[]) {
    /*
     Define Shaders
     */

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

    Shader shader = Shader(vertex_shader, fragment_shader);
    Window mainWindow = Window(1280, 720, "Hephaestus Game Engine", &shader, init, destroy, tick, update, render);
    
    mainWindow.windowLoop();
    return 0;
}
