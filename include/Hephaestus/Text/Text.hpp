/*
    Text.hpp
    Zachary lineman
    12/7/21
    
    =================
    DESCRIPTION
    =================
*/

#include <iostream>

#include <glm/glm.hpp>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H//"freetype2/freetype/freetype.h"
#include <Hephaestus//Shader/Shader.hpp>
#include "Hephaestus/HephaestusUtility.hpp"

#ifndef OLYMPUS_TEXT_HPP
#define OLYMPUS_TEXT_HPP

class Text {
public:
    Text(std::string text, std::string fontPath, glm::vec2 position, glm::vec4 color, int pixelHeight = 24);
    Text(std::string text, std::string fontPath, glm::vec4 color, ScreenAnchor _anchor, glm::vec2 _anchorOffset, AnchorPoint _anchorPoint, int pixelHeight = 24);

    /* Positioning */
    glm::vec2 position { 0.0, 0.0 };
    glm::vec2 relativePositionOffset { 0.0, 0.0 };
    PositioningType positionType = absolute;

    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    std::map<char, Character> characters;
    float scale = 1.0f;
    int pixelHeight = 24;

    glm::vec2 dimensions { 0, 0 };
    float textAlignmentOffset { 0 };

    std::string text { };
    std::string fontPath { };
    std::string fontID { };

    glm::vec4 color { 0.0, 0.0, 0.0, 0.0 };
    bool registered = false;

    void draw();
    bool hidden = false;
    // Call functions are needed because we need to recalculate the position when this changes
    void setAnchorPosition(ScreenAnchor anchorPosition);
    void setAnchorPoint(AnchorPoint anchorPoint);

    void assign(Shader* shader, GLuint* vbo, GLuint* vao, glm::mat4* projection, glm::vec2 screenSize, std::map<char, Character> characters);
    void updateScreenSize(glm::vec2 screenSize);
private:
    glm::mat4* projection;
    Shader* textShader;
    GLuint* VBO;
    GLuint* VAO;

    AnchorPoint anchorPoint { pointBottomLeft };

    glm::vec2 screenSize { 0.0, 0.0 };
    ScreenAnchor anchorPosition { center };
    glm::vec2 anchorPositionBeforeOffset { 0.0, 0.0 };
    void updateAnchorPosition();
};


#endif //OLYMPUS_TEXT_HPP
