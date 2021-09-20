//
//  GeometryManager.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.


#include "GeometryManager.hpp"

GeometryManager::GeometryManager() { }

void GeometryManager::draw() {
    for(int i = 0; i < geometryBuffers.size(); i++) {
        geometryBuffers[i].draw();
    }
}

void GeometryManager::updateBuffer(string id) {
    
}

void GeometryManager::addTriangle(Vertex vertices[6]) {
    vector<Vertex> holdVertices = {};
    for(int i = 0; i < 3; i++) {
        holdVertices.push_back(vertices[i]);
    }

    GeometryBuffer buffer = GeometryBuffer("background", holdVertices, shader, "./resources/missing.jpg");
    geometryBuffers.push_back(buffer);
}

//void GeometryManager::addCube(Vertex *vertices) {
//}
