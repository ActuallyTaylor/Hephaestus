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
#include "../../Text/TextManager.hpp"
#include "../../Function.hpp"

class Button: public UIElement {
public:
    using UIElement::UIElement;

    void setOnClick(Function _onClick);
    void setOnHover(Function _onHover);

    void setBackgroundColor(glm::vec4 color);
    void setNormalText(std::string _text, std::string fontPath, glm::vec4 color);

    void primaryFunction() override;
protected:
    Function onClick;
    Function onHover;
    Text buttonText = {"", "", {0,0}, {0,0,0,0}};

    GLubyte backgroundColorImage[128][128][4];

    bool needsToAddText = false;

    void refresh() override;
};


#endif //OLYMPUS_BUTTON_HPP
