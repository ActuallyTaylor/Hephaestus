//
//  Vertex.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#include "Vertex.hpp"

Vertex::Vertex(Vector3 coordinate, Vector3 color, Vector2 texture) {
    this->coordinate = coordinate;
    this->color = color;
    this->texture = texture;
}

bool Vertex::operator==(Vertex &rhs) {
    return (this->coordinate == rhs.coordinate) && (this->color == rhs.color) && (this->texture == rhs.texture);
}

bool Vertex::operator!=(Vertex &rhs) {
    return !(*this==rhs);
}

bool Vertex::operator==(const Vertex &rhs) {
    return (this->coordinate == rhs.coordinate) && (this->color == rhs.color) && (this->texture == rhs.texture);
}

bool Vertex::operator!=(const Vertex &rhs) {
    return !(*this==rhs);
}

