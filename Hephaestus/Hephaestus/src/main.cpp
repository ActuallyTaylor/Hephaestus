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
#include "Triangle.hpp"

using namespace std;

/*
 Define Shaders
 */

const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";


const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
"}";

int currentTriangleID = 1;
vector<Triangle> triangles;

static void addTriangle(GLfloat vertices[]) {
    Triangle newTriangle = Triangle(vertices, currentTriangleID - 1);
    newTriangle.id = currentTriangleID;
    triangles.push_back(newTriangle);
    currentTriangleID += 1;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, const char * argv[]) {
    // GLFW Initialization
    GLFWwindow* window;
    
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }
    
    // macOS specific flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hephaestus Game Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    
    //Add the key call
    glfwSetKeyCallback(window, key_callback);
    
    // Build Shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    
    // Combine into a GPU shader program
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    
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

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        /*
         Render here
        */
        
        // Clean the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);

        for(int i = 0; i < triangles.size(); i++) {
            triangles[i].Draw();
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
