//
//  Keybind.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/8/21.
//

#include "Keybind.hpp"

Keybind::Keybind(int keyCode, int action, Function executionFunction) {
    this->keyCode = keyCode;
    this->action = action;
    this->executionCode = executionFunction;
}

void Keybind::execute() {
    executionCode();
}
