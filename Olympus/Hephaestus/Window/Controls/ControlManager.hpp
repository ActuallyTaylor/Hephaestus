/*
    ControlManager.hpp
    Zachary lineman
    11/5/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_CONTROLMANAGER_HPP
#define OLYMPUS_CONTROLMANAGER_HPP

#include <vector>

#include "./Keybind/Keybind.hpp"

class ControlManager {
public:
    ControlManager();

    std::vector<Keybind> keybindings;

    void addKeybind(Keybind keybind);

    void executeKeybinds(int keycode, int action);
};


#endif //OLYMPUS_CONTROLMANAGER_HPP
