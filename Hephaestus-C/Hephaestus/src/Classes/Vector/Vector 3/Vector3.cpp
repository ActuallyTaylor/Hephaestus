//
//  Vector3.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#include "Vector3.hpp"

Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Vector3::operator==(Vector3 &rhs) {
    return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z);
}

bool Vector3::operator!=(Vector3 &rhs) {
    return !(*this==rhs);
}

bool Vector3::operator==(const Vector3 &rhs) {
    return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z);
}

bool Vector3::operator!=(const Vector3 &rhs) {
    return !(*this==rhs);
}

