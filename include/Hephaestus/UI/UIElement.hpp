/*
    UIElement.hpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_UIELEMENT_HPP
#define OLYMPUS_UIELEMENT_HPP

#include <string>
#include <vector>
#include <Hephaestus/libs/stb_image.hpp>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Hephaestus
#include <Hephaestus/Shader/Shader.hpp>
#include "Hephaestus/Text/TextManager.hpp"

class UIElement {
public:
    glm::vec3 position { 0.0, 0.0, 0.0 };
    glm::vec3 absolutePositionOffset { 0.0, 0.0, 0.0 };
    glm::vec3 relativePositionOffset { 0.0, 0.0, 0.0 };
    PositioningType positionType = absolute;

    explicit UIElement(glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    explicit UIElement(ScreenAnchor anchor, glm::vec3 anchorOffset, AnchorPoint _anchorPoint, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});

    void addShader(Shader shader);

    glm::vec2 dimensions { 0.0, 0.0 };
    glm::vec3 rotation { 0.0, 0.0, 0.0 };

    glm::vec4 tintColor { 0.0, 0.0, 0.0, 1.0 };

    bool hidden = false;
    bool isClicked = false;

    Shader shader { "Hold UIManager Shader" };

    void draw();
    void updateScreenDimensions(int width, int height);
    void setTextManager(TextManager *_textManager);

    // Call functions are needed because we need to recalculate the position when this changes
    void setAnchorPosition(ScreenAnchor anchorPosition);
    void setAnchorPoint(AnchorPoint anchorPoint);

    virtual void primaryFunction();

    TextManager *textManager;
    virtual void refresh();
protected:
    glm::mat4 projection { };
    glm::vec2 screenSize { };

    GLuint VBO, VAO, EBO, textureAtlas;

    void createVirtualBufferObject();

    void createTexture(const std::string& texturePath, SamplingType samplingType = linear);

    ScreenAnchor anchorPosition { center };
    AnchorPoint anchorPoint { pointBottomLeft };
    glm::vec3 anchorPositionBeforeOffset { 0.0, 0.0, 0.0 };
    void updateAnchorPosition();
    void updateAnchorPointPosition();
};


#endif //OLYMPUS_UIELEMENT_HPP
