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
#include "../Library/stb_image.hpp"

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Hephaestus
#include "../Shader/Shader.hpp"
#include "../Text/TextManager.hpp"

class UIElement {
public:
    enum ScreenAnchor { topLeft, topCenter, topRight, centerLeft, center, centerRight, bottomLeft, bottomCenter, bottomRight };
    enum PositioningType { absolute, relative };
    enum AnchorPoint { pointTopLeft, pointTopCenter, pointTopRight, pointCenterLeft, pointCenter, pointCenterRight, pointBottomLeft, pointBottomCenter, pointBottomRight };

    glm::vec3 position { 0.0, 0.0, 0.0 };
    glm::vec3 relativePositionOffset { 0.0, 0.0, 0.0 };
    PositioningType positionType = absolute;

    UIElement(std::string _texturePath, glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    UIElement(glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});

    UIElement(ScreenAnchor anchor, glm::vec3 anchorOffset, std::string _texturePath, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    UIElement(ScreenAnchor anchor, glm::vec3 anchorOffset, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});

    void addShader(Shader shader);

    glm::vec2 dimensions { 0.0, 0.0 };
    glm::vec3 rotation { 0.0, 0.0, 0.0 };

    glm::vec4 tintColor { 0.0, 0.0, 0.0, 1.0 };

    bool isClicked = false;

    Shader shader { "Hold UIManager Shader" };

    void draw();
    void updateScreenDimensions(int width, int height);
    void setTexture(std::string texturePath);
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

    void createTexture(const std::string& texturePath);
    void createVirtualBufferObject();

    ScreenAnchor anchorPosition { center };
    AnchorPoint anchorPoint { pointBottomLeft };
    glm::vec3 anchorPositionBeforeOffset { 0.0, 0.0, 0.0 };
    void updateAnchorPosition();
    void updateTextOffset();
};


#endif //OLYMPUS_UIELEMENT_HPP
