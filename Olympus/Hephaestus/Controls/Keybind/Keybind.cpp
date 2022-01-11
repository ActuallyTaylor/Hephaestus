/*
    Keybind.cpp
    Zachary lineman
    11/5/21
    
    =================
    DESCRIPTION
    =================
*/

#include "Keybind.hpp"

Keybind::Keybind(int inKeyCode, int inAction, Function inExecutionFunction) {
    keyCode = inKeyCode;
    action = inAction;
    executionCode = inExecutionFunction;
}

void Keybind::execute() {
    if (executionCode != nullptr) {
        executionCode();
    }
}