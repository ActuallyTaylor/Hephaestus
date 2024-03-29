/*
    Camera.hpp
    Zachary lineman
    11/10/21
    
    =================
    Camera Header Class
    An object that represents an OpenGL camera.
    =================
*/

#include <iostream>

#ifndef OLYMPUS_CAMERA_HPP
#define OLYMPUS_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Hephaestus/Function.hpp"

class Camera {
public:
    Camera();
    glm::vec3 position {0.0f, 0.0f, 3.0f};
    glm::vec3 rotation {0.0f, 0.0f, 0.0f};
    glm::vec3* target;

    bool isUICamera = false;

    void setPosition(glm::vec3 newPosition);
    glm::vec3 getPosition();

    void setRotation(glm::vec3 newRotation);
    glm::vec3 getRotation();

    void setTarget(glm::vec3* newTarget);
    glm::vec3* getTarget();

    glm::mat4 getView();
};

#endif //OLYMPUS_CAMERA_HPP */