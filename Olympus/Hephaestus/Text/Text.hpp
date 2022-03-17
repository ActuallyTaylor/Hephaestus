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
#include FT_FREETYPE_H
#include "../Shader/Shader.hpp"

#ifndef OLYMPUS_TEXT_HPP
#define OLYMPUS_TEXT_HPP

class Text {
public:
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    std::string text { };
    std::string fontPath { };
    std::string fontID { };

    glm::vec2 position { 0.0, 0.0 };
    glm::vec4 color { 0.0, 0.0, 0.0, 0.0 };

    std::map<char, Character> characters;
    float scale = 1.0f;
    int pixelHeight = 24;
    bool registered = false;

    Text(std::string text, std::string fontPath, glm::vec2 position, glm::vec4 color, int pixelHeight = 24);

    void draw();
    void assign(Shader* shader, GLuint* vbo, GLuint* vao, glm::mat4* projection, std::map<char, Character> characters);

private:
    glm::mat4* projection;
    Shader* textShader;
    GLuint* VBO;
    GLuint* VAO;
};


#endif //OLYMPUS_TEXT_HPP
