/*
    Sprite.cpp
    Zachary lineman
    11/3/21
    
    =================
    DESCRIPTION
    =================
*/
#define STB_IMAGE_IMPLEMENTATION

#include "Sprite.hpp"

Sprite::Sprite(Shader sentShader, std::string texturePath) {
    shader = sentShader;
    createTexture(texturePath);
}

Sprite::Sprite(Shader sentShader, std::string texturePath, GLfloat inX, GLfloat inY, GLfloat inZ) {
    shader = sentShader;
    x = inX;
    y = inY;
    z = inZ;
    createTexture(texturePath);
}

void Sprite::createTexture(std::string texturePath) {
    /*
     Create Texture
     */
    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    glGenTextures(1, &textureAtlas);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);
}

void Sprite::setX(GLfloat xValue) {
    x = xValue;
}

GLfloat Sprite::getX() {
    return x;
}

void Sprite::setY(GLfloat yValue) {

}

GLfloat Sprite::getY() {
    return y;
}

void Sprite::setZ(GLfloat zValue) {

}

GLfloat Sprite::getZ() {
    return z;
}