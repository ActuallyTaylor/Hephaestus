/*
    Keybind.hpp
    Zachary lineman
    11/5/21
    
    =================
    DESCRIPTION
    =================
*/
typedef void (*Function)();

#ifndef OLYMPUS_KEYBIND_HPP
#define OLYMPUS_KEYBIND_HPP

class Keybind {
public:
    Keybind(int keyCode, int action, Function executionCode);

    int keyCode;
    int action;
    Function executionCode;

    void execute();
};


#endif //OLYMPUS_KEYBIND_HPP
