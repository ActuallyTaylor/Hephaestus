//
//  Keybind.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/8/21.
//

#ifndef Keybind_hpp
#define Keybind_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef void(*Function)();

class Keybind {
public:
    Keybind(int keyCode, int action, Function executionCode);
    
    int keyCode;
    int action;
    Function executionCode;

    void execute();
};

#endif /* Keybind_hpp */
