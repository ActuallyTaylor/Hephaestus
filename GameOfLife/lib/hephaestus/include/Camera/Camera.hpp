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
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../Function.hpp"

class Camera {
private:
    Function updatePositionCallback;
    Function updateRotationCallback;
    Function updateTargetCallback;
public:
    Camera();
    glm::vec3 position {0.0f, 0.0f, 3.0f};
    glm::vec3 rotation {0.0f, 0.0f, 0.0f};
    glm::vec3 target   {0.0f, 0.0f, 0.0f};

    bool isUICamera = false;

    void setPosition(glm::vec3 newPosition);
    glm::vec3 getPosition();

    void setRotation(glm::vec3 newRotation);
    glm::vec3 getRotation();

    void setTarget(glm::vec3 newTarget);
    glm::vec3 getTarget();

//    glm::vec3 getDirection();

    void setUpdatePositionCallback(Function callback);
    void setUpdateRotationCallback(Function callback);
    void setUpdateTargetCallback(Function callback);

    glm::mat4 getView();
};

#endif //OLYMPUS_CAMERA_HPP */