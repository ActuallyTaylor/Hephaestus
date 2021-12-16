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
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../Shader/Shader.hpp"
#include "Text.hpp"

#ifndef OLYMPUS_TEXTMANAGER_HPP
#define OLYMPUS_TEXTMANAGER_HPP

// https://learnopengl.com/In-Practice/Text-Rendering
class TextManager {
    GLuint VBO;
    GLuint VAO;
    Shader textShader = Shader("./Hephaestus/Shaders/Font.vert", "./Hephaestus/Shaders/Font.frag");

    glm::mat4 projection;
    glm::vec2 screenSize { 0.0, 0.0 };

    std::map<std::string, std::map<char, Text::Character>> fonts;

    vector<Text *> textObjects;
public:
    TextManager();
    void setup();

    int loadFont(std::string filePath);
    void addText(Text *text);
    void draw();
    void updateScreenDimensions(int width, int height);
};

#endif //OLYMPUS_TEXTMANAGER_HPP
