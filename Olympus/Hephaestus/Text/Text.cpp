/*
    Text.cpp
    Zachary lineman
    12/7/21
    
    =================
    DESCRIPTION
    =================
*/

#include "Text.hpp"
#include <utility>

Text::Text(std::string text, std::string fontPath, glm::vec2 position, glm::vec4 color, int pixelHeight) {
    this->text = std::move(text);
    this->position = position;
    this->color = color;
    this->fontPath = std::move(fontPath);
    this->pixelHeight = pixelHeight;
    this->fontID = this->fontPath + "(" + std::to_string(this->pixelHeight) + ")";
}

void Text::assign(Shader* shader, GLuint* vbo, GLuint* vao, glm::mat4* _projection, glm::vec2 screenSize, std::map<char, Character> _characters) {
    this->textShader = shader;
    this->VBO = vbo;
    this->VAO = vao;
    this->projection = _projection;
    this->characters = std::move(_characters);
    this->screenSize = screenSize;
    updateAnchorPosition();
    updateTextOffset();
}

void Text::draw() {
    glm::vec2 _position = this->position;

    if(positionType == relative) {
        // Get the calculated relative position and add the offset specific by the user.
        _position = anchorPositionBeforeOffset + relativePositionOffset;
    }

    _position = { _position.x + this->textAlignmentOffset, _position.y };

    textShader->use();
    textShader->setVector3f("textColor", color.x, color.y, color.z);
    textShader->setMatrix4("projection", *projection);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(*VAO);

    for(char c: text) {
        Character ch = characters[c];

        float xpos = _position.x + ch.Bearing.x * scale;
        float ypos = _position.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        // update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        _position.x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::setAnchorPosition(Text::ScreenAnchor anchorPosition) {
    if (this->positionType == absolute) {
        std::cout << "Warning: Make sure to set positionType to relative for anchor position to be used";
    }
    this->anchorPosition = anchorPosition;
    updateAnchorPosition();
}

void Text::updateAnchorPosition() {
    switch(this->anchorPosition) {
        case topLeft:
            anchorPositionBeforeOffset = { 0, screenSize.y};
            break;
        case topCenter:
            anchorPositionBeforeOffset = { screenSize.x / 2, screenSize.y};
            break;
        case topRight:
            anchorPositionBeforeOffset = { screenSize.x, screenSize.y / 2};
            break;
        case centerLeft:
            anchorPositionBeforeOffset = { 0, screenSize.y / 2};
            break;
        case center:
            anchorPositionBeforeOffset = { screenSize.x / 2, screenSize.y / 2};
            break;
        case centerRight:
            anchorPositionBeforeOffset = { screenSize.x, screenSize.y / 2};
            break;
        case bottomLeft:
            anchorPositionBeforeOffset = { 0, 0};
            break;
        case bottomCenter:
            anchorPositionBeforeOffset = { screenSize.x / 2, 0};
            break;
        case bottomRight:
            anchorPositionBeforeOffset = { screenSize.x, 0};
            break;
    }
}

void Text::setTextAlignment(TextAlignment alignment) {
    this->textAlignment = alignment;
    updateTextOffset();
}

void Text::updateTextOffset() {
    for(char c: text) {
        Character ch = characters[c];
        float w = ch.Size.x * scale;
        totalWidth += w;
    }

    switch(this->textAlignment) {
        case alignLeft:
            textAlignmentOffset = 0;
            break;
        case alignCenter:
            textAlignmentOffset = -(totalWidth / 2);
            break;
        case alignRight:
            textAlignmentOffset = 0;
            break;
    }
}

void Text::updateScreenSize(glm::vec2 screenSize) {
    this->screenSize = screenSize;
    updateAnchorPosition();
}