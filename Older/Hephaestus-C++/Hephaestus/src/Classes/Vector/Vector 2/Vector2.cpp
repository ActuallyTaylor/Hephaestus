//
//  Vector2.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#include "Vector2.hpp"

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(GLfloat x, GLfloat y) {
    this->x = x;
    this->y = y;
}

bool Vector2::operator==(Vector2 &rhs) {
    return (this->x == rhs.x) && (this->y == rhs.y);
}

bool Vector2::operator!=(Vector2 &rhs) {
    return !(*this==rhs);
}

bool Vector2::operator==(const Vector2 &rhs) {
    return (this->x == rhs.x) && (this->y == rhs.y);
}

bool Vector2::operator!=(const Vector2 &rhs) {
    return !(*this==rhs);
}


