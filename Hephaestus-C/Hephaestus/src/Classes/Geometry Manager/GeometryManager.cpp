//
//  GeometryManager.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.
//

#include "GeometryManager.hpp"

GeometryManager::GeometryManager() {}

void GeometryManager::draw() {
    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, (triangles.size() * 3));
}

void GeometryManager::createVirtualBufferObject() {
    CompressedData compressedData = compressTriangleVertices();
    vector<GLfloat> vertices = compressedData.vertices;
    vector<unsigned int> indices = compressedData.indexes;

    // Finish setting up index based rendering. Should save some memory.
    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    
//    printf("Index Count: %lu\n", indices.size());
//
//    for(int i = 0; i < indices.size(); i++) {
//        printf("%d,", indices[i]);
//    }
//    printf("\n");
//
//    printf("Vertex Count: %lu\n", vertices.size());
//    for(int i = 0; i < vertices.size(); i++) {
//        printf("%f,", vertices[i]);
//    }
//    printf("\n");
    
    this->indiceCount = indices.size();
}

CompressedData GeometryManager::compressTriangleVertices() {
    vector<Vector3> conjoinedVertices;

    for(int i = 0; i < triangles.size(); i++) {
        for(int n = 0; n < triangles[i].vertexAmount(); n++) {
            auto iter = find(conjoinedVertices.begin(), conjoinedVertices.end(), triangles[i].vertices[n]);
            if (iter == conjoinedVertices.end()) {
                conjoinedVertices.push_back(triangles[i].vertices[n]);
            }
        }
    }
    
    vector<unsigned int> indexes;

    for(int i = 0; i < triangles.size(); i++) {
        for(int n = 0; n < triangles[i].vertexAmount(); n++) {
            Vector3 vertex = triangles[i].vertices[n];
            auto iter = find(conjoinedVertices.begin(), conjoinedVertices.end(), vertex);
            if (iter != conjoinedVertices.end()) {
                int index = distance(conjoinedVertices.begin(), iter);
                indexes.push_back(index);
            }
        }
    }
    
    vector<GLfloat> floatVertices;

    for(int i = 0; i < conjoinedVertices.size(); i++) {
        floatVertices.push_back(conjoinedVertices[i].x);
        floatVertices.push_back(conjoinedVertices[i].y);
        floatVertices.push_back(conjoinedVertices[i].z);
    }
    
    return CompressedData(floatVertices, indexes);
}


void GeometryManager::addTriangle(Vector3 *vertices) {
    Triangle holdTriangle = Triangle(vertices);
    triangles.push_back(holdTriangle);
}
