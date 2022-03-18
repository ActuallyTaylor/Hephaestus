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
    explicit Button(std::string backgroundImagePath, glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    explicit Button(std::string backgroundImagePath, ScreenAnchor anchor, glm::vec3 anchorOffset, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});

    explicit Button(glm::vec4 backgroundColor, glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    explicit Button(glm::vec4 backgroundColor, ScreenAnchor anchor, glm::vec3 anchorOffset, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});

    void setOnClick(Function _onClick);
    void setOnHover(Function _onHover);

    void setBackgroundColor(glm::vec4 color);
    void setNormalText(std::string _text, std::string fontPath, glm::vec4 color);

    void primaryFunction() override;
protected:
    Function onClick;
    Function onHover;
    Text buttonText = {"", "", {0,0}, {0,0,0,0}, 24};

    GLubyte backgroundColorImage[128][128][4];

    bool needsToAddText = false;

    void refresh() override;
};


#endif //OLYMPUS_BUTTON_HPP
