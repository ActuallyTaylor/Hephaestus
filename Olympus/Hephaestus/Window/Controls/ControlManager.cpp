/*
    ControlManager.cpp
    Zachary lineman
    11/5/21
    
    =================
    Implementations for the ControlManager.hpp class functions
    =================
*/

#include "ControlManager.hpp"

ControlManager::ControlManager() = default;

void ControlManager::executeKeybinds(int keycode, int action) {
    for(Keybind & keybinding : keybindings) {
        if (keybinding.keyCode == keycode && keybinding.action == action) {
            keybinding.execute();
        }
    }
}

void ControlManager::addKeybind(Keybind keybind) {
    keybindings.push_back(keybind);
}
