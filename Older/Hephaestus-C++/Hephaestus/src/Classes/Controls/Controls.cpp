//
//  Controls.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/19/21.
//

#include "Controls.hpp"

Controls::Controls() {
}

void Controls::addKeybind(Keybind keybind) {
    keybindings.push_back(keybind);
}

void Controls::executeKeybinds(int keycode, int action) {
    for(int i = 0; i < keybindings.size(); i++) {
        if (keybindings[i].keyCode == keycode && keybindings[i].action == action) {
            keybindings[i].execute();
        }
    }
}
