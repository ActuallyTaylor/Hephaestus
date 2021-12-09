/*
    Button.cpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#include "Button.hpp"

void Button::setOnClick(Function _onClick) {
    onClick = _onClick;
}

void Button::setOnHover(Function _onHover) {
    onHover = _onHover;
}

void Button::primaryFunction() {
    UIElement::primaryFunction();
    onClick();
}

