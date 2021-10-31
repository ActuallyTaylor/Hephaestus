/*
    Window.hpp
    Zachary Lineman
    October 28th 2021

    =================
    This class will hold the code to handle windows in the hephaesuts engine.
    =================
*/

#ifndef FILE_hpp
#define FILE_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    GLfloat width;
    GLfloat height;

public:
    Window(GLfloat width, GLfloat height);
};


#endif