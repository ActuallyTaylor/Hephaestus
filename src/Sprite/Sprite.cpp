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

#include <Hephaestus/Sprite/Sprite.hpp>

Sprite::Sprite() {
    position = {300.0f, 300.0f, 0.0f};
    dimensions = {50.0f, 50.0f};
    rotation = {0.0f, 0.0f, 0.0f};
}

Sprite::Sprite(std::string _id, std::string _texturePath, SamplingType _samplingType, glm::vec3 _position, glm::vec2 _dimensions, glm::vec3 _rotation) {
    id = _id;
    position = _position;
    dimensions = _dimensions;
    rotation = _rotation;
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    samplingType = _samplingType;

    createTexture(_texturePath, samplingType);
    createVirtualBufferObject();
}

Sprite::~Sprite() {
//    printf("Destroyed Sprite\n");
}

void Sprite::createTexture(const std::string& texturePath, SamplingType samplingType) {
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, translateSamplingType(samplingType));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, translateSamplingType(samplingType));

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
        printf("Failed to load texture: %s, using backup texture\n", texturePath.c_str());
        unsigned char *data = stbi_load("./Hephaestus/null.png", &width, &height, &nrChannels, 0);
        if (data) {
            if (nrChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            } else if (nrChannels == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            printf("Failed to load backup texture");
        }
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
    if(hidden) {
        return;
    }

    shader.use();
    glm::mat4 model = translate(glm::mat4(1.0f), position);

    // Apply the rotation of the sprite
    model = rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = scale(model, glm::vec3(dimensions, 1.0f));
    model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));

    glm::mat4 view = camera->getView();

    shader.setMatrix4("model", model);
    shader.setMatrix4("view", view);
    shader.setMatrix4("projection", projection);
//    textShader->setVector3f("tintColor", tintColor);

    glBindVertexArray(VAO);

    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::setTexture(const std::string& texturePath) {
    createTexture(texturePath, samplingType);
}

void Sprite::updateScreenDimensions(int width, int height) {
    screenSize = glm::vec2(width, height);
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    createVirtualBufferObject();
}

glm::vec3 Sprite::getPosition() {
    return position;
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

glm::vec3 Sprite::getRotation() {
    return rotation;
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

glm::vec2 Sprite::getDimensions() {
    return dimensions;
}

void Sprite::setSize(glm::vec2 dimension) {
    dimensions = dimension;
}

float Sprite::getWidth() {
    return dimensions.x;
}

void Sprite::setWidth(GLfloat width) {
    dimensions.x = width;
}

float Sprite::getHeight() {
    return dimensions.y;
}

void Sprite::setHeight(GLfloat height) {
    dimensions.y = height;
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

void Sprite::move(double deltaTime) { }

float Sprite::getRadius() {
    return dimensions.x / 2;
}

void Sprite::registerSprite() {
    registered = true;
}

bool Sprite::getRegistered() {
    return registered;
}

bool Sprite::physicscCollidable() {
    return isPhysicscCollidable;
}

void Sprite::setPhysicscCollidable(bool _collidable) {
    isPhysicscCollidable = _collidable;
}

bool Sprite::canMovePhysically() {
    return false;
}

bool Sprite::collidable() {
    return isCollidable;
}

void Sprite::setCollidable(bool _collidable) {
    isCollidable = _collidable;
}
