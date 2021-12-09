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

typedef void (*Function)();

class Button: public UIElement {
public:
    using UIElement::UIElement;

    void setOnClick(Function _onClick);
    void setOnHover(Function _onHover);

    void primaryFunction() override;
protected:
    Function onClick;
    Function onHover;
};


#endif //OLYMPUS_BUTTON_HPP
