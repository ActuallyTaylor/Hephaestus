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
    UIElement(std::string _texturePath, glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    void addShader(Shader shader);

    glm::vec3 position { 0.0, 0.0, 0.0 };
    glm::vec2 dimensions { 0.0, 0.0 };
    glm::vec3 rotation { 0.0, 0.0, 0.0 };

    glm::vec4 tintColor { 0.0, 0.0, 0.0, 1.0 };

    bool isClicked = false;

    Shader shader { "Hold UIManager Shader" };

    void draw();
    void updateScreenDimensions(int width, int height);
    void setTexture(std::string texturePath);
    void setTextManager(TextManager *_textManager);

    virtual void primaryFunction();

    TextManager *textManager;
    virtual void refresh();
protected:
    glm::mat4 projection { };
    glm::vec2 screenSize { };

    GLuint VBO, VAO, EBO, textureAtlas;

    void createTexture(const std::string& texturePath);
    void createVirtualBufferObject();
};


#endif //OLYMPUS_UIELEMENT_HPP
