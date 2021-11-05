//
//  Triangle.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Triangle.hpp"

Triangle::Triangle(Vertex triangleVertices[3]) {
    for(int i = 0; i < 3; i++) {
        vertices.push_back(triangleVertices[i]);
    }
}

int Triangle::vertexAmount() {
    return vertices.size();
}

