/*
    Sprite.cpp
    Zachary lineman
    11/3/21
    
    =================
    Implementations for the Sprite.hpp class.
    =================
*/
#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#include "Sprite.hpp"


Sprite::Sprite(Shader inShader, std::string texturePath, glm::vec3 inPosition, glm::vec2 inSize, glm::vec3 inRotation) {
    shader = inShader;
    position = inPosition;
    size = inSize;
    rotation = inRotation;

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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);
}

void Sprite::createVirtualBufferObject() {
    float vertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // top left
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

void Sprite::draw() {
    shader.use();
    glm::mat4 model = translate(glm::mat4(1.0f), position);

    // Apply the rotation of the sprite
    model = rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = scale(model, glm::vec3(size, 1.0f));

    glm::mat4 view = camera->getView();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenSize.x), static_cast<float>(screenSize.y), 0.0f, -1000.0f, 1000.0f);

    shader.setMatrix4("model", model);

    shader.setMatrix4("view", view);

    shader.setMatrix4("projection", projection);

    glBindVertexArray(VAO);

    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::setPosition(glm::vec3 inPosition) {
    position = inPosition;
}

float Sprite::getX() {
    return position.x;
}

void Sprite::setX(GLfloat xValue) {
    position.x = xValue;
}

float Sprite::getY() {
    return position.y;
}

void Sprite::setY(GLfloat yValue) {
    position.y = yValue;
}

float Sprite::getZ() {
    return position.z;
}

void Sprite::setZ(GLfloat zValue) {
    position.z = zValue;
}

void Sprite::setTexture(std::string texturePath) {
    createTexture(texturePath);
}

void Sprite::updateScreenDimensions(int width, int height) {
    printf("Update Dimensions %d, %d\n", width, height);
    screenSize = glm::vec2(width, height);
    createVirtualBufferObject();
}

glm::vec3 Sprite::getPosition() {
    return position;
}


void Sprite::setRotation(glm::vec3 inRotation) {
    rotation = inRotation;
}

float Sprite::getRoll() {
    return rotation.x;
}

void Sprite::setRoll(GLfloat roll) {
    rotation.x = roll;
}

float Sprite::getPitch() {
    return rotation.y;
}

void Sprite::setPitch(GLfloat pitch) {
    rotation.y = pitch;
}

float Sprite::getYaw() {
    return rotation.z;
}

void Sprite::setYaw(GLfloat yaw) {
    rotation.z = yaw;
}

void Sprite::setSize(glm::vec2 inSize) {
    size = inSize;
}

float Sprite::getWidth() {
    return size.x;
}

void Sprite::setWidth(GLfloat width) {
    size.x = width;
}

float Sprite::getHeight() {
    return size.y;
}

void Sprite::setHeight(GLfloat height) {
    size.y = height;
}

void Sprite::updateCamera(Camera* newCamera) {
    camera = newCamera;
}

void Sprite::setShape(Sprite::Shape shape) {
    spriteShape = shape;
}

Sprite::Shape Sprite::getShape() {
    return spriteShape;
}

void Sprite::move(float deltaTime) {

}

float Sprite::getRadius() {
    return size.x / 2;
}
