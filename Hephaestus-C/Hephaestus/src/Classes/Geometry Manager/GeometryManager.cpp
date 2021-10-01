//
//  GeometryManager.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.


#include "GeometryManager.hpp"

GeometryManager::GeometryManager() { }

void GeometryManager::draw() {
    for(int i = 0; i < spriteRenderers.size(); i++) {
        spriteRenderers[i].drawAllSprites();
    }
}

void GeometryManager::updateBuffer(string id) {
    
}

void GeometryManager::addTriangle(Vertex vertices[6]) {
//    vector<Vertex> holdVertices = {};
//    for(int i = 0; i < 3; i++) {
//        holdVertices.push_back(vertices[i]);
//    }
//
//    GeometryBuffer buffer = GeometryBuffer("triangle", holdVertices, shader, "./resources/missing.jpg");
//    geometryBuffers.push_back(buffer);
}

void GeometryManager::addCube(Vertex *vertices) {
//    vector<Vertex> holdVertices = {};
//    for(int i = 0; i < 36; i++) {
//        holdVertices.push_back(vertices[i]);
//    }
//
//    GeometryBuffer buffer = GeometryBuffer("background", holdVertices, shader, "./resources/missing.jpg");
//    geometryBuffers.push_back(buffer);
}

void GeometryManager::addSprite(string id, string texturePath, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    SpriteRenderer spriteRenderer = SpriteRenderer(shader, width, height);
    spriteRenderer.registerSprite(id, texturePath, position, size, rotate, color);
    
    spriteRenderers.push_back(spriteRenderer);
}
