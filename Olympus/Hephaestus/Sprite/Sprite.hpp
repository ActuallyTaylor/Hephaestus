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
    glm::vec3 position { };
    glm::vec2 size { };
    glm::vec3 rotation { };

    void createTexture(std::string texturePath);
    void createVirtualBufferObject();

    Shader shader;
    GLuint VBO, VAO, EBO, textureAtlas;

public:
    Sprite(Shader shader, std::string texturePath,
           glm::vec3 position = glm::vec3(300.0f, 300.0f, 0.0f),
           glm::vec2 size = glm::vec2(50.0f, 50.0f),
           glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));

    void draw();

    // MARK: Sprite Position
    void setPosition(glm::vec3 position);

    // X coordinate
    float getX();
    void setX(GLfloat x);

    // Y coordinate
    float getY();
    void setY(GLfloat y);

    // Z coordinate
    float getZ();
    void setZ(GLfloat z);
};

#endif //OLYMPUS_SPRITE_HPP
