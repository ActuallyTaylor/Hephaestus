//
//  GeometryManager.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "GeometryManager.hpp"

GeometryManager::GeometryManager() {
    
}

int GeometryManager::createVirtualBufferObject() {
    vector<GLfloat> compressedVertices = compressTriangleVertices();

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, compressedVertices.size() * sizeof(float), compressedVertices.data(), GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    return compressedVertices.size();
}

vector<GLfloat> GeometryManager::compressTriangleVertices() {
    vector<GLfloat> compressedVertices;
    printf("Test: %lu", triangles.size());
    for(int i = 0; i < triangles.size(); i++) {
        for(int n = 0; n < triangles[i].vertexAmount(); n++) {
            compressedVertices.push_back(triangles[i].vertices[n]);
        }
    }
    return compressedVertices;
}

void GeometryManager::addTriangle(GLfloat *vertices) {
    Triangle holdTriangle = Triangle(vertices);
    triangles.push_back(holdTriangle);
}

//static void addTriangle(GLfloat (&vertices)[9]) {
//}
//
//unsigned long loadVertices() {
//    GLuint vbo = 0;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(float), triangleVertices.data(), GL_STATIC_DRAW);
//
//    GLuint vao = 0;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//    return triangleVertices.size();
//}

