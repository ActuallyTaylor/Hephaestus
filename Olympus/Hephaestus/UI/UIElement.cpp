/*
    UIElement.cpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#include "UIElement.hpp"

UIElement::UIElement(std::string _texturePath, glm::vec3 _position, glm::vec2 _dimensions, glm::vec3 _rotation) {
    position = _position;
    dimensions = _dimensions;
    rotation = _rotation;

    createTexture(_texturePath);
}



void UIElement::createTexture(const std::string& texturePath) {
    /*
     Create Texture
     */
    stbi_set_flip_vertically_on_load(true);
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
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);
}

void UIElement::createVirtualBufferObject() {
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

void UIElement::draw() {
    shader.use();
    glm::mat4 model = translate(glm::mat4(1.0f), position);

    // Apply the rotation of the sprite
    model = rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = scale(model, glm::vec3(dimensions, 1.0f));
    model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));

    shader.setMatrix4("model", model);
    shader.setMatrix4("view", glm::mat4(1.0f));
    shader.setMatrix4("projection", projection);
//    shader.setVector4f("tintColor", tintColor);

    glBindVertexArray(VAO);

    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void UIElement::updateScreenDimensions(int width, int height) {
    screenSize = glm::vec2(width, height);
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    createVirtualBufferObject();
}

void UIElement::setTexture(std::string texturePath) {
    createTexture(texturePath);
}

void UIElement::primaryFunction() {}

void UIElement::setTextManager(TextManager *_textManager) {
    textManager = _textManager;
    refresh();
}

void UIElement::refresh() {}

void UIElement::addShader(Shader _shader) {
    shader = _shader;
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    shader.setMatrix4("projection", projection);
    shader.setup();

    createVirtualBufferObject();
}