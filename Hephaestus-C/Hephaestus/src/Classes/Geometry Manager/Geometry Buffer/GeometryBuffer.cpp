//
//  GeometryBuffer.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/20/21.
//

#include "GeometryBuffer.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GeometryBuffer::GeometryBuffer() { }

GeometryBuffer::GeometryBuffer(string id, vector<Vertex> vertices, Shader shader, string texturePath) {
    this->id = id;
    this->vertices = vertices;
    this->shader = shader;

    this->shader.setup();

    /*
     Create Texture
     */
    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    glGenTextures(1, &textureAtlas);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);

    createVirtualBufferObject();
}

void GeometryBuffer::createVirtualBufferObject() {
//    printf("=== UPDATE CYCLE ===\n");
    CompressedData compressedData = compressTriangleVertices();
    vector<GLfloat> vertices = compressedData.vertices;
    vector<unsigned int> indices = compressedData.indexes;

    // Finish setting up index based rendering. Should save some memory.
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);
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
    
    printf("Index Count: %lu\n", indices.size());

    for(int i = 0; i < indices.size(); i++) {
        printf("%d,", indices[i]);
        if((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    printf("Vertex Count: %lu\n", vertices.size());
    for(int i = 0; i < vertices.size(); i++) {
        printf("%f,", vertices[i]);
        if((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    
    this->indiceCount = indices.size();
//    printf("=== END UPDATE CYCLE ===\n");
}

CompressedData GeometryBuffer::compressTriangleVertices() {
    vector<Vertex> conjoinedVertices;

    for(int i = 0; i < vertices.size(); i++) {
        auto iter = find(conjoinedVertices.begin(), conjoinedVertices.end(), vertices[i]);
        if (iter == conjoinedVertices.end()) {
            conjoinedVertices.push_back(vertices[i]);
        }
    }
    
    vector<unsigned int> indexes;

    for(int i = 0; i < vertices.size(); i++) {
        Vertex vertex = vertices[i];
        auto iter = find(conjoinedVertices.begin(), conjoinedVertices.end(), vertex);
        if (iter != conjoinedVertices.end()) {
            int index = std::distance(conjoinedVertices.begin(), iter);
            indexes.push_back(index);
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

void GeometryBuffer::draw() {
    shader.use();
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);

//    printf("Drawing Triangles: %d \n", indiceCount);
    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
}
