/*
    Sprite.cpp
    Zachary lineman
    11/3/21
    
    =================
    DESCRIPTION
    =================
*/
#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#include "Sprite.hpp"

Sprite::Sprite(Shader sentShader, std::string texturePath) {
    shader = sentShader;
    createTexture(texturePath);
    createVirtualBufferObject();
}

Sprite::Sprite(Shader sentShader, std::string texturePath, GLfloat inX, GLfloat inY, GLfloat inZ) {
    shader = sentShader;
    position.x = inX;
    position.y = inY;
    position.z = inZ;
    createTexture(texturePath);
    createVirtualBufferObject();
}

void Sprite::createTexture(std::string texturePath) {
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
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void Sprite::setX(GLfloat xValue) {
    position.x = xValue;
}

GLfloat Sprite::getX() {
    return position.x;
}

void Sprite::setY(GLfloat yValue) {
    position.y = yValue;
}

GLfloat Sprite::getY() {
    return position.y;
}

void Sprite::setZ(GLfloat zValue) {
    position.z = zValue;
}

GLfloat Sprite::getZ() {
    return position.z;
}

void Sprite::draw() {
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = translate(model, position);

    model = rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = scale(model, glm::vec3(size, 1.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = translate(view, glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 projection;
    projection = glm::ortho(0.0f, static_cast<float>(720), static_cast<float>(720), 0.0f, -1000.0f, 1000.0f);

    shader.setMatrix4("model", model);

    shader.setMatrix4("view", view);

    shader.setMatrix4("projection", projection);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
