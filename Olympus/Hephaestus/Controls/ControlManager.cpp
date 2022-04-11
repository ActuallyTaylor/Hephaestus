/*
    ControlManager.cpp
    Zachary lineman
    11/5/21
    
    =================
    Implementations for the ControlManager.hpp class functions
    =================
*/
#include <iostream>

#include "ControlManager.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../HephaestusEnums.hpp"

ControlManager::ControlManager() = default;

void ControlManager::executeKeybinds(int keycode, int action) {
    if(action == GLFW_PRESS) {
        heldKeys[keycode] = 0;
    } else if (action == GLFW_RELEASE) {
        heldKeys.erase(keycode);
    }

    for(Keybind & keybinding : keybindings) {
        if ((keybinding.keyCode == keycode || keybinding.keyCode == HEPHAESTUS_ANY_KEY) && keybinding.action == action) {
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

void ControlManager::executeHolding() {
    for(Keybind & keybind : keybindings) {
        if(heldKeys.count(keybind.keyCode) > 0 && keybind.action == GLFW_PRESS) { // We found the keybind is being held
            keybind.execute();
        }
    }
}
