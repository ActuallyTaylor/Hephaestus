//
//  GeometryManager.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.


#include "GeometryManager.hpp"

GeometryManager::GeometryManager() {}

void GeometryManager::setupShader() {
    this->shader.setup();
}

void GeometryManager::draw() {
    for(int i = 0; i < sprites.size(); i++) {
        sprites[i].draw();
    }
}

void GeometryManager::updateBuffer(string id) {
    
}

void GeometryManager::updateDimensions(vec2 dimensions) {
    this->dimensions = dimensions;
    
    for(int i = 0; i < sprites.size(); i++) {
        sprites[i].screenDimensions = dimensions;
    }
}

void GeometryManager::clear() {
    sprites.clear();
}

void GeometryManager::addTriangle(Vertex vertices[3]) {
    vector<Vertex> holdVertices = {};
    for(int i = 0; i < 3; i++) {
        holdVertices.push_back(vertices[i]);
    }

    Sprite buffer = Sprite("background", holdVertices, shader, "./resources/missing.jpg");
    sprites.push_back(buffer);
}

void GeometryManager::addSquare(Vertex vertices[6]) {
    vector<Vertex> holdVertices = {};
    for(int i = 0; i < 6; i++) {
        holdVertices.push_back(vertices[i]);
    }

    Sprite buffer = Sprite("background", holdVertices, shader, "./resources/missing.jpg");
    sprites.push_back(buffer);
}

void GeometryManager::addCube(Vertex *vertices) {
    vector<Vertex> holdVertices = {};
    for(int i = 0; i < 36; i++) {
        holdVertices.push_back(vertices[i]);
    }

    Sprite buffer = Sprite("background", holdVertices, shader, "./resources/missing.jpg");
    sprites.push_back(buffer);
}


void GeometryManager::addSprite(string id, string texturePath) {
    Sprite sprite = Sprite(id, shader, texturePath);
    sprite.screenDimensions = dimensions;
    sprites.push_back(sprite);
}

void GeometryManager::addSprite(string id, string texturePath, vec3 position = vec3(1.0f), vec2 size = vec2(1.0f), vec3 rotation =  vec3(1.0f)) {
    Sprite sprite = Sprite(id, shader, texturePath);
    sprite.position = position;
    sprite.size = size;
    sprite.rotation = rotation;
    sprite.screenDimensions = dimensions;
    sprites.push_back(sprite);
}

void GeometryManager::moveSprite(string id, vec3 position) {
    for(int i = 0; i < sprites.size(); i++) {
        Sprite & sprite = sprites[i];
        if (sprite.id == id) {
            sprite.updatePosition(position);
        }
    }
}

void GeometryManager::rotateSprite(string id, vec3 rotation) {
    for(int i = 0; i < sprites.size(); i++) {
        Sprite & sprite = sprites[i];
        if (sprite.id == id) {
            sprite.updateRotation(rotation);
        }
    }
}

void GeometryManager::scaleSprite(string id, vec2 size) {
    for(int i = 0; i < sprites.size(); i++) {
        Sprite & sprite = sprites[i];
        if (sprite.id == id) {
            sprite.updateSize(size);
        }
    }
}

Sprite& GeometryManager::getSprite(string id) {
    for(int i = 0; i < sprites.size(); i++) {
        if (sprites[i].id == id) {
            return sprites[i];
        }
    }
    return sprites[0];
}
