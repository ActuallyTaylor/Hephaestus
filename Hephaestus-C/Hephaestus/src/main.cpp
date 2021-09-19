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

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

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
    
    geometryManager.loadTextureAtlas("./Resources/wall.jpg");
    
//    Vertex firstTrianglePoints[] = {
//        Vertex(Vector3(0.5f,  0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
//        Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
//        Vertex(Vector3(-0.5f,  0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f))
//    };
//    geometryManager.addTriangle(firstTrianglePoints);
//
//    Vertex secondTrianglePoints[] = {
//        Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
//        Vertex(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
//        Vertex(Vector3(-0.5f,  0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f))
//    };
//    geometryManager.addTriangle(secondTrianglePoints);
    
    Vertex cubePoints[] = {
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),

        Vertex(Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),

        Vertex(Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(-0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),

        Vertex(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),

        Vertex(Vector3(-0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
        Vertex(Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(-0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)),
    };
    geometryManager.addCube(cubePoints);
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
    // create transformations

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(1.0f, 0.0f, 1.0f));
//    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
   
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    int modelLoc = glGetUniformLocation(shader.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(shader.shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
    Window mainWindow = Window(720, 720, "Hephaestus Game Engine", &shader, &geometryManager, init, destroy, tick, update, render);
    
    //Add the key call
    glfwSetKeyCallback(mainWindow.window, key_callback);

    mainWindow.windowLoop();
    
    return 0;
}
