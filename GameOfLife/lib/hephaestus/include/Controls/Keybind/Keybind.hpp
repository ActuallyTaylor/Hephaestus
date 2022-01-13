/*
    Keybind.hpp
    Zachary lineman
    11/5/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_KEYBIND_HPP
#define OLYMPUS_KEYBIND_HPP
#include "../../Function.hpp"

class Keybind {
public:
    Keybind(int keyCode, int action, Function executionCode);

    int keyCode;
    int action;
    Function executionCode;

    void execute();
};


#endif //OLYMPUS_KEYBIND_HPP
