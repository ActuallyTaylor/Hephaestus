/*
    ControlManager.cpp
    Zachary lineman
    11/5/21
    
    =================
    Implementations for the ControlManager.hpp class functions
    =================
*/

#include "ControlManager.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

ControlManager::ControlManager() = default;

void ControlManager::executeKeybinds(int keycode, int action) {
    for(Keybind & keybinding : keybindings) {
        if (keybinding.keyCode == keycode && keybinding.action == action) {
            keybinding.execute();
        }
    }}

void ControlManager::addKeybind(Keybind keybind) {
    keybindings.push_back(keybind);
}

void ControlManager::addDrag(Keybind keybind) {
    dragBindings.push_back(keybind);
}

void ControlManager::executeDragging() {
    for(Keybind & keybinding : dragBindings) {
        if(keybinding.keyCode == GLFW_MOUSE_BUTTON_LEFT) {
            if(leftDown) {
                keybinding.execute();
            }
        } else if (keybinding.keyCode == GLFW_MOUSE_BUTTON_RIGHT) {
            if(rightDown) {
                keybinding.execute();
            }
        }
    }
}
