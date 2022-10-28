/*
    Keybind.cpp
    Zachary lineman
    11/5/21
    
    =================
    DESCRIPTION
    =================
*/

#include <Hephaestus/Controls/Keybind/Keybind.hpp>

#include <utility>

Keybind::Keybind(int inKeyCode, int inAction, Function inExecutionFunction, bool executesOnHold) {
    this->keyCode = inKeyCode;
    this->action = inAction;
    this->executesOnHold = executesOnHold;
    this->executionCode = std::move(inExecutionFunction);
}

void Keybind::execute() {
    if (executionCode != nullptr) {
        executionCode();
    }
}