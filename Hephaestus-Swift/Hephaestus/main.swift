//
//  main.swift
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

import Foundation
import OpenGL

// Initialize GLFW
if(glfwInit() == 0) {
    print("Failed to initialize GLFW! I'm out!")
    exit(-1)
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_SAMPLES, 4);

// Open a window and attach an OpenGL context to the window surface
guard let window = glfwCreateWindow(640, 480, "Hephaestus Game Engine", nil, nil)
else {
    print("Failed to open a window! I'm out!")
    glfwTerminate()
    exit(-1)
}

// Set the window context current
glfwMakeContextCurrent(window)

// Print the OpenGL version currently enabled on your machine
let version = String(cString: glGetString(UInt32(GL_VERSION)))
print(version)

// Use red to clear the screen
glClearColor(1, 0, 0, 1)

var vertex_shader = GLchar("""
    #version 400
    in vec3 vp;
    void main() {
        gl_Position = vec4(vp, 1.0);
    }
    """)
var fragment_shader = GLchar("""
    #version 400
    out vec4 frag_colour
    void main() {
        frag_colour = vec4(1.0, 1.0, 1.0, 1.0);
    }
    """)!

// Build Shaders
let vs: GLuint = glCreateShader(GLenum(GL_VERTEX_SHADER));
glShaderSource(vs, 1, &vertex_shader, nil);
glCompileShader(vs);
let fs: GLuint = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fs, 1, &fragment_shader, nil);
glCompileShader(fs);

// Combine into a GPU shader program
let shader_programme: GLuint = glCreateProgram();
glAttachShader(shader_programme, fs);
glAttachShader(shader_programme, vs);
glLinkProgram(shader_programme);

let firstTrianglePoints: [GLfloat] = [
    -0.5,  0.5,  0.0,
    0.5, -0.5,  0.0,
    -0.5, -0.5,  0.0,
]

while (glfwWindowShouldClose(window) == 0) {
    // Clear the screen (window background)
    glClear(UInt32(GL_COLOR_BUFFER_BIT))

    // Draw a square using the (deprecated) fixed pipeline functionality
//    glColor3f(1.0, 1.0, 0.0)
//    glBegin(UInt32(GL_QUADS))
//    glVertex2f(-0.5, -0.5)
//    glVertex2f(0.5, -0.5)
//    glVertex2f(0.5, 0.5)
//    glVertex2f(-0.5, 0.5)
//    glEnd()

    // Swap front and back buffers for the current window
    glfwSwapBuffers(window)

    // Poll for events
    glfwPollEvents()
}

// Destroy the window and its context
glfwDestroyWindow(window)

// Terminate GLFW
glfwTerminate()
