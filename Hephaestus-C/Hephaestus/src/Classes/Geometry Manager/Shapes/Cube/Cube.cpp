//
//  Cube.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/18/21.
//

#include "Cube.hpp"

Cube::Cube(Vertex triangleVertices[36]) {
    for(int i = 0; i < 36; i++) {
        vertices.push_back(triangleVertices[i]);
    }
}

int Cube::vertexAmount() {
    return vertices.size();
}


