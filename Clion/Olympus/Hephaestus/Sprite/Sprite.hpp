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

// GLM Math
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


class Sprite {
private:
    glm::vec3 position = glm::vec3(300.0f, 300.0f, 0.0f);
    glm::vec2 size = glm::vec2(50.0f, 50.0f);
    //                    x  ,  y  ,  z
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    void createTexture(std::string texturePath);
    void createVirtualBufferObject();

    Shader shader;
    GLuint VBO, VAO, EBO, textureAtlas;

public:
    Sprite(Shader shader, std::string texturePath);
    Sprite(Shader shader, std::string texturePath, GLfloat x, GLfloat y, GLfloat z);

    void draw();

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
