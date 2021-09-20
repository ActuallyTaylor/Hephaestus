//
//  GeometryManager.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/13/21.


#include "GeometryManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GeometryManager::GeometryManager(Shader *shader) {
    this->shader = shader;
}

void GeometryManager::draw() {
    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, (triangles.size() * 3));
}

void GeometryManager::createVirtualBufferObject() {
//    printf("=== UPDATE CYCLE ===\n");
    CompressedData compressedData = compressTriangleVertices();
    vector<GLfloat> vertices = compressedData.vertices;
    vector<unsigned int> indices = compressedData.indexes;

    // Finish setting up index based rendering. Should save some memory.
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
     
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
//    printf("Index Count: %lu\n", indices.size());
//
//    for(int i = 0; i < indices.size(); i++) {
//        printf("%d,", indices[i]);
//        if((i + 1) % 8 == 0) {
//            printf("\n");
//        }
//    }
//    printf("\n");
//
//    printf("Vertex Count: %lu\n", vertices.size());
//    for(int i = 0; i < vertices.size(); i++) {
//        printf("%f,", vertices[i]);
//        if((i + 1) % 8 == 0) {
//            printf("\n");
//        }
//    }
//    printf("\n");
    
    this->indiceCount = indices.size();
//    printf("=== END UPDATE CYCLE ===\n");
}

CompressedData GeometryManager::compressTriangleVertices() {
    vector<Vertex> conjoinedVertices;

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
            Vertex vertex = triangles[i].vertices[n];
            auto iter = find(conjoinedVertices.begin(), conjoinedVertices.end(), vertex);
            if (iter != conjoinedVertices.end()) {
                int index = std::distance(conjoinedVertices.begin(), iter);
                indexes.push_back(index);
            }
        }
    }
    
    vector<GLfloat> floatVertices;

    for(int i = 0; i < conjoinedVertices.size(); i++) {
        floatVertices.push_back(conjoinedVertices[i].coordinate.x);
        floatVertices.push_back(conjoinedVertices[i].coordinate.y);
        floatVertices.push_back(conjoinedVertices[i].coordinate.z);
        floatVertices.push_back(conjoinedVertices[i].color.x);
        floatVertices.push_back(conjoinedVertices[i].color.y);
        floatVertices.push_back(conjoinedVertices[i].color.z);
        floatVertices.push_back(conjoinedVertices[i].texture.x);
        floatVertices.push_back(conjoinedVertices[i].texture.y);
    }
    
    return CompressedData(floatVertices, indexes);
}


void GeometryManager::addTriangle(Vertex *vertices) {
    Triangle holdTriangle = Triangle(vertices);
    triangles.push_back(holdTriangle);
}

void GeometryManager::addCube(Vertex *vertices) {
    Cube holdTriangle = Cube(vertices);
    cubes.push_back(holdTriangle);
}

void GeometryManager::clear() {
    triangles.clear();
}


void GeometryManager::loadTextureAtlas(string atlasPath) {
    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    glGenTextures(1, &textureAtlas);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(atlasPath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);
}

void GeometryManager::renderSprite(string texture, vec2 position, vec2 size, float rotate, vec3 color) {
    
}
