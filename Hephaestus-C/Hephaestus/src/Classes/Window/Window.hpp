//
//  Window.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

/*
 Window
 
 The window class holds the rendering logic and frame rate things
 */

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <strings.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
#include "GeometryManager.hpp"

using namespace std;

typedef void(*Function)();

class Window {
    GLfloat width;
    GLfloat height;

public:
    Window (GLfloat windowWidth, GLfloat windowHeight, char* windowName, GeometryManager &geometryManager, Function init, Function destroy, Function tick, Function update, Function render);
    Function init, destroy, tick, update, render;
    void windowLoop ();
    GLFWwindow *window;
    GeometryManager geometryManager;
    
private:
    void _init ();
    void _destroy ();
    void _tick ();
    void _update ();
    void _render ();
    
    void windowCallback(GLFWwindow* window, int width, int height);
};

/*
 class Triangle {
     GLfloat vertices[9];
 public:
     Triangle (GLfloat vertices[9], int vboNumb);
     int id;
     void Draw ();
 };
 */
#endif /* Window_hpp */
