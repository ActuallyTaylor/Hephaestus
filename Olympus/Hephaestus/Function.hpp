/*
    Function.hpp
    Zachary lineman
    1/12/22
    
    =================
    DESCRIPTION
    =================
*/
#pragma once
#include <functional>

#ifndef OLYMPUS_FUNCTION_HPP
#define OLYMPUS_FUNCTION_HPP

typedef std::function<void()> Function;
typedef std::function<void(std::string spriteID)> CollisionCallback;

//template<typename T>
//
//struct Function {
//    void (T::*Function)() = { };
//};

#endif //OLYMPUS_FUNCTION_HPP
