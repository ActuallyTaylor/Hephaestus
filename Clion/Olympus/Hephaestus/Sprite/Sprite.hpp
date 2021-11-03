/*
    Sprite.hpp
    Zachary lineman
    11/3/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_SPRITE_HPP
#define OLYMPUS_SPRITE_HPP
#include "../Shader/Shader.hpp"
#include "../Library/stb_image.hpp"

class Sprite {
private:
    GLfloat x { 0 };
    GLfloat y { 0 };
    GLfloat z { 0 };

    void createTexture(std::string texturePath);

    Shader shader;
    GLuint VBO, VAO, EBO, textureAtlas;

public:
    Sprite(Shader shader, std::string texturePath);
    Sprite(Shader shader, std::string texturePath, GLfloat x, GLfloat y, GLfloat z);
//    Sprite(GLfloat x, GLfloat y);

    // Mess with X coordinate
    void setX(GLfloat xValue);
    GLfloat getX();

    // Mess with Y coordinate
    void setY(GLfloat yValue);
    GLfloat getY();

    //M Mess with Z coordinate
    void setZ(GLfloat zValue);
    GLfloat getZ();
};

#endif //OLYMPUS_SPRITE_HPP
