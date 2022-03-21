/*
    ControlManager.hpp
    Zachary lineman
    11/5/21
    
    =================
    Control Manager Header Class
    Contains all the logic for executing and storing keybinds.
    =================
*/

#ifndef OLYMPUS_CONTROLMANAGER_HPP
#define OLYMPUS_CONTROLMANAGER_HPP

#include <vector>
#include <map>

#include "./Keybind/Keybind.hpp"

class ControlManager {
public:
    ControlManager();

    std::vector<Keybind> keybindings { };
    std::vector<Keybind> dragBindings { };
    std::map<int, int> heldKeys { };


    bool leftDown = false;
    bool rightDown = false;

    void addKeybind(Keybind keybind);
    void addDrag(Keybind keybind);

    void executeKeybinds(int keycode, int action);
    void executeDragging();
    void executeHolding();
};


#endif //OLYMPUS_CONTROLMANAGER_HPP
