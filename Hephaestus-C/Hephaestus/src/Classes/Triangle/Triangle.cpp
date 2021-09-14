//
//  Triangle.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "Triangle.hpp"

Triangle::Triangle(GLfloat triangleVertices[9]) {
    for(int i = 0; i < 9; i++) {
        vertices.push_back(triangleVertices[i]);
    }
}

int Triangle::vertexAmount() {
    return vertices.size();
}
