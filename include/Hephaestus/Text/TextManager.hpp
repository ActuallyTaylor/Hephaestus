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
#include FT_FREETYPE_H //"freetype2/freetype/freetype.h"
#include <Hephaestus//Shader/Shader.hpp>
#include "Text.hpp"

#ifndef OLYMPUS_TEXTMANAGER_HPP
#define OLYMPUS_TEXTMANAGER_HPP

// https://learnopengl.com/In-Practice/Text-Rendering
class TextManager {
    GLuint VBO;
    GLuint VAO;

    const char *defaultVertexShader = R""""(
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
)"""";

    const char *defaultFragmentShader = R""""(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
)"""";

    Shader textShader = Shader("Text Manager Shader", defaultVertexShader, defaultFragmentShader);

    glm::mat4 projection;
    glm::vec2 screenSize { 0.0, 0.0 };

    std::map<std::string, std::map<char, Text::Character>> fonts;

    vector<Text *> textObjects;
public:
    TextManager();
    void setup();

    int loadFont(std::string filePath, int pixelHeight, SamplingType samplingType = linear);
    void addText(Text *text);
    void draw();
    void updateScreenDimensions(int width, int height);
};

#endif //OLYMPUS_TEXTMANAGER_HPP
