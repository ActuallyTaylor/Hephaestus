//
//  Sprite.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/27/21.
//

#include "Sprite.hpp"

Sprite::Sprite(string id, string texturePath, vec2 position, vec2 size, float rotate, vec3 color) {
    this->id = id;
    this->texturePath = texturePath;
    this->position = position;
    this->size = size;
    this->rotate = rotate;
    this->color = color;
}
