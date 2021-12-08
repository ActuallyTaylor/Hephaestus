/*
    Button.hpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_BUTTON_HPP
#define OLYMPUS_BUTTON_HPP


#include "../UIElement.hpp"

class Button: public UIElement {
    using UIElement::UIElement;

    Function onClick;
    Function onHover;
};

#endif //OLYMPUS_BUTTON_HPP
