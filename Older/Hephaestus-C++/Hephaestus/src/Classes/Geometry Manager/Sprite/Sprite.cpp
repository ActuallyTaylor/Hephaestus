//
//  Sprite.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/20/21.
//

#include "Sprite.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GLM_ENABLE_EXPERIMENTAL

Sprite::Sprite(string id, vector<Vertex> vertices, Shader shader, string texturePath) {
    this->id = id;
    this->vertices = vertices;
    this->shader = shader;

    createTexture(texturePath);
    createVirtualBufferObject();
}

Sprite::Sprite(string id, Shader shader, string texturePath) {
    this->id = id;
    this->vertices = {
        Vertex(vec3(0.5f,  0.5f, 0.0f), vec2(1.0f, 1.0f)),
        Vertex(vec3(0.5f, -0.5f, 0.0f), vec2(1.0f, 0.0f)),
        Vertex(vec3(-0.5f,  0.5f, 0.0f), vec2(0.0f, 1.0f)),
        Vertex(vec3(0.5f, -0.5f, 0.0f), vec2(1.0f, 0.0f)),
        Vertex(vec3(-0.5f, -0.5f, 0.0f), vec2(0.0f, 0.0f)),
        Vertex(vec3(-0.5f,  0.5f, 0.0f), vec2(0.0f, 1.0f))
    };
    this->shader = shader;

    this->shader.setup();

    createTexture(texturePath);
    createVirtualBufferObject();
}


void Sprite::createTexture(string texturePath) {
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
}

void Sprite::createVirtualBufferObject() {
    CompressedData compressedData = compressTriangleVertices();
    vector<GLfloat> vertices = compressedData.vertices;
    vector<unsigned int> indices = compressedData.indexes;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
     
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    this->indiceCount = indices.size();
//    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
}

CompressedData Sprite::compressTriangleVertices() {
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
        floatVertices.push_back(conjoinedVertices[i].texture.x);
        floatVertices.push_back(conjoinedVertices[i].texture.y);
    }
    
    return CompressedData(floatVertices, indexes);
}

void Sprite::draw() {
    shader.use();

    mat4 model = mat4(1.0f);
    model = translate(model, position);
    
//    rotation = vec3(glfwGetTime() * 100, glfwGetTime()  * 100, glfwGetTime() * 100);
    model = rotate(model, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
    
    model = scale(model, vec3(size, 1.0f));

    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = ortho(0.0f, static_cast<float>(screenDimensions.x), static_cast<float>(screenDimensions.y), 0.0f, -1000.0f, 1000.0f);
    //glm::perspective(glm::radians(45.0f), 720.0f / 720.0f, 0.1f, 100.0f);
    
    shader.setMatrix4("model", model);
    
    shader.setMatrix4("view", view);
    
    shader.setMatrix4("projection", projection);
    
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);

//    printf("Drawing Triangles: %d \n", indiceCount);
    glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
}

void Sprite::updatePosition(vec3 newPosition) {
    position = newPosition;
}

void Sprite::updateSize(vec2 newSize) {
    size = newSize;
}

void Sprite::updateRotation(vec3 newRotation) {
    rotation = newRotation;
}

vec3 Sprite::getPosition() {
    return position;
}

vec3 Sprite::getRotation() {
    return rotation;
}

vec2 Sprite::getSize() {
    return size;
}

