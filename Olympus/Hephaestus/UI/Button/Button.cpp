/*
    Button.cpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#include "Button.hpp"
#include <utility>

void Button::setBackgroundColor(glm::vec4 color) {
    if (tintColor != color) {
        tintColor = color;

        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                backgroundColorImage[i][j][0] = (GLubyte) color.x;
                backgroundColorImage[i][j][1] = (GLubyte) color.y;
                backgroundColorImage[i][j][2] = (GLubyte) color.z;
                backgroundColorImage[i][j][3] = (GLubyte) color.w;
            }
        }
    }
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureAtlas);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundColorImage);
}

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

void Button::setNormalText(std::string _text, std::string fontPath, glm::vec4 color) {
    buttonText.text = std::move(_text);
    buttonText.fontPath = std::move(fontPath);
    buttonText.color = color;

    if (!buttonText.registered) {
        if(textManager != nullptr) {
            textManager->addText(&buttonText);
        } else {
            needsToAddText = true;
        }
    }
}

void Button::refresh() {
    if(needsToAddText) {
        textManager->addText(&buttonText);
    }
}

