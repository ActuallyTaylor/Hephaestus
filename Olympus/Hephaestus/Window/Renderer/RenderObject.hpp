/*
    RenderObject.hpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_RENDEROBJECT_HPP
#define OLYMPUS_RENDEROBJECT_HPP

#include <string>
#include <vector>
#include "../../Library/stb_image.hpp"

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Hephaestus
#include "../../Shader/Shader.hpp"
#include "../Camera/Camera.hpp"

// GLM Math
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

class RenderObject {
protected:
    glm::mat4 projection { };
    glm::vec2 screenSize { };

    void createTexture(std::string texturePath);
    void createVirtualBufferObject();
public:
    glm::vec3 position { };
    glm::vec3 rotation { };
    glm::vec2 dimensions { };

    Shader shader;
    GLuint VBO, VAO, EBO, textureAtlas;

    Camera* camera;

    // MARK: Drawing Functions
    void draw();

    void setTexture(std::string texturePath);

    void updateScreenDimensions(int width, int height);

};


#endif //OLYMPUS_RENDEROBJECT_HPP
