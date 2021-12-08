/*
    Sprite.cpp
    Zachary lineman
    11/3/21
    
    =================
    Implementations for the Sprite.hpp class.
    =================
*/
#include "Sprite.hpp"

glm::vec3 Sprite::getPosition() {
    return position;
}

void Sprite::setPosition(glm::vec3 inPosition) {
    position = inPosition;
}

float Sprite::getX() {
    return position.x;
}

void Sprite::setX(GLfloat xValue) {
    position.x = xValue;
}

float Sprite::getY() {
    return position.y;
}

void Sprite::setY(GLfloat yValue) {
    position.y = yValue;
}

float Sprite::getZ() {
    return position.z;
}

void Sprite::setZ(GLfloat zValue) {
    position.z = zValue;
}

glm::vec3 Sprite::getRotation() {
    return rotation;
}

void Sprite::setRotation(glm::vec3 inRotation) {
    rotation = inRotation;
}

float Sprite::getRoll() {
    return rotation.x;
}

void Sprite::setRoll(GLfloat roll) {
    rotation.x = roll;
}

float Sprite::getPitch() {
    return rotation.y;
}

void Sprite::setPitch(GLfloat pitch) {
    rotation.y = pitch;
}

float Sprite::getYaw() {
    return rotation.z;
}

void Sprite::setYaw(GLfloat yaw) {
    rotation.z = yaw;
}

glm::vec2 Sprite::getSize() {
    return dimensions;
}

void Sprite::setSize(glm::vec2 _dimensions) {
    dimensions = _dimensions;
}

float Sprite::getWidth() {
    return dimensions.x;
}

void Sprite::setWidth(GLfloat width) {
    dimensions.x = width;
}

float Sprite::getHeight() {
    return dimensions.y;
}

void Sprite::setHeight(GLfloat height) {
    dimensions.y = height;
}

void Sprite::updateCamera(Camera* newCamera) {
    camera = newCamera;
}

void Sprite::setShape(Sprite::Shape shape) {
    spriteShape = shape;
}

Sprite::Shape Sprite::getShape() {
    return spriteShape;
}

void Sprite::move(double deltaTime) {

}

float Sprite::getRadius() {
    return dimensions.x / 2;
}

void Sprite::registerSprite() {
    registered = true;
}

bool Sprite::getRegistered() const {
    return registered;
}
