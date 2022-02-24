/*
    Text.cpp
    Zachary lineman
    12/3/21

    =================
    DESCRIPTION
    =================
*/

#include <iostream>
#include "TextManager.hpp"

TextManager::TextManager() {}

void TextManager::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glMatrixMode (GL_PROJECTION);

    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    textShader.setMatrix4("projection", projection);
    textShader.setup();
}

int TextManager::loadFont(std::string filePath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, filePath.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }

    // set dimensions to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 24);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set
    std::map<char, Text::Character> fontCharacters;
    for (unsigned char c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // now store character for later use
        Text::Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };
        fontCharacters.insert(std::pair<char, Text::Character>(c, character));
    }
    fonts.insert(std::pair<std::string, std::map<char, Text::Character>>(filePath, fontCharacters));

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return 0;
}

void TextManager::draw() {
    for( Text *text : textObjects) {
        text->draw();
    }
}

void TextManager::addText(Text *text) {
    if(text->registered) { return; }
    std::map<char, Text::Character> font = fonts[text->fontPath];

    if (fonts.find(text->fontPath) != fonts.end() && !fonts.empty()) {
        text->assign(&textShader, &VBO, &VAO, &projection, font);
        text->registered = true;
        textObjects.push_back(text);
    } else {
        loadFont(text->fontPath);
        font = fonts[text->fontPath];

        text->assign(&textShader, &VBO, &VAO, &projection, font);
        text->registered = true;
        textObjects.push_back(text);
    }
}

void TextManager::updateScreenDimensions(int width, int height) {
    screenSize = glm::vec2(width, height);
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
}
