/*
    Text.hpp
    Zachary lineman
    12/3/21
    
    =================
    DESCRIPTION
    =================
*/

#include <glm/glm.hpp>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../Shader/Shader.hpp"

#ifndef OLYMPUS_TEXTMANAGER_HPP
#define OLYMPUS_TEXTMANAGER_HPP

// https://learnopengl.com/In-Practice/Text-Rendering
class TextManager {
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    Shader textShader = Shader("./Hephaestus/Shaders/font.vert", "./Hephaestus/Shaders/font.frag");
    GLuint VBO {};
    GLuint VAO {};

    std::map<char, Character> Characters;
    glm::mat4 projection;
public:
    TextManager();
    void setup();

    int loadFont(std::string filePath);
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif //OLYMPUS_TEXTMANAGER_HPP
