/*
    UIElement.cpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#include <Hephaestus/UI/UIElement.hpp>

#include <utility>

UIElement::UIElement(glm::vec3 _position, glm::vec2 _dimensions, glm::vec3 _rotation) {
    position = _position;
    dimensions = _dimensions;
    rotation = _rotation;

    updateAnchorPosition();
    updateAnchorPointPosition();
}

UIElement::UIElement(ScreenAnchor _anchor, glm::vec3 _anchorOffset, AnchorPoint _anchorPoint, glm::vec2 _dimensions, glm::vec3 _rotation) {
    positionType = relative;
    anchorPosition = _anchor;
    relativePositionOffset = _anchorOffset;
    anchorPoint = _anchorPoint;
    dimensions = _dimensions;
    rotation = _rotation;

    updateAnchorPosition();
    updateAnchorPointPosition();
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
    if (hidden) { return; }
    shader.use();
    glm::vec3 _position = anchorPositionBeforeOffset + absolutePositionOffset;

    if(positionType == relative) {
        // Get the calculated relative position and add the offset specific by the user.
        _position = anchorPositionBeforeOffset + relativePositionOffset;
    }

    glm::mat4 model = translate(glm::mat4(1.0f), _position);

    // Apply the rotation of the sprite
    model = rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, glm::radians( rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
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

void UIElement::createTexture(const std::string& texturePath, SamplingType samplingType) {
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

void UIElement::updateScreenDimensions(int width, int height) {
    screenSize = glm::vec2(width, height);
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    createVirtualBufferObject();
        updateAnchorPosition();
        updateAnchorPointPosition();
}

void UIElement::primaryFunction() {}

void UIElement::setTextManager(TextManager *_textManager) {
    textManager = _textManager;
    refresh();
}

void UIElement::refresh() {}

void UIElement::addShader(Shader _shader) {
    shader = std::move(_shader);
    projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1000.0f, 1000.0f);
    shader.setMatrix4("projection", projection);
    shader.setup();

    createVirtualBufferObject();
}

void UIElement::setAnchorPoint(AnchorPoint anchorPoint) {
//    if (this->positionType == absolute) {
//        std::cout << "Warning: Make sure to set positionType to relative for anchor position to be used";
//    }
    this->anchorPoint = anchorPoint;
    updateAnchorPosition();
    updateAnchorPointPosition();
}

void UIElement::setAnchorPosition(ScreenAnchor anchorPosition) {
    if (this->positionType == absolute) {
        std::cout << "Warning: Make sure to set positionType to relative for anchor position to be used";
    }
    this->anchorPosition = anchorPosition;
        updateAnchorPosition();
        updateAnchorPointPosition();
}

void UIElement::updateAnchorPosition() {
    if(positionType == relative) {
        switch(this->anchorPosition) {
            case topLeft:
                anchorPositionBeforeOffset = { 0, screenSize.y, 0};
                break;
            case topCenter:
                anchorPositionBeforeOffset = { screenSize.x / 2, screenSize.y, 0};
                break;
            case topRight:
                anchorPositionBeforeOffset = { screenSize.x, screenSize.y / 2, 0};
                break;
            case centerLeft:
                anchorPositionBeforeOffset = { 0, screenSize.y / 2, 0};
                break;
            case center:
                anchorPositionBeforeOffset = { screenSize.x / 2, screenSize.y / 2, 0};
                break;
            case centerRight:
                anchorPositionBeforeOffset = { screenSize.x, screenSize.y / 2, 0};
                break;
            case bottomLeft:
                anchorPositionBeforeOffset = { 0, 0, 0};
                break;
            case bottomCenter:
                anchorPositionBeforeOffset = { screenSize.x / 2, 0, 0};
                break;
            case bottomRight:
                anchorPositionBeforeOffset = { screenSize.x, 0, 0};
                break;
        }
    } else if (positionType == absolute) {
        anchorPositionBeforeOffset = position;
    }
    position = anchorPositionBeforeOffset;
}

void UIElement::updateAnchorPointPosition() {
    switch(this->anchorPoint) {
        case pointTopLeft:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x, anchorPositionBeforeOffset.y  - dimensions.y, anchorPositionBeforeOffset.z };
            break;
        case pointTopCenter:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x  - (dimensions.x / 2), anchorPositionBeforeOffset.y - dimensions.y, anchorPositionBeforeOffset.z };
            break;
        case pointTopRight:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x - dimensions.x, anchorPositionBeforeOffset.y - dimensions.y, anchorPositionBeforeOffset.z };
            break;
        case pointCenterLeft:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x, anchorPositionBeforeOffset.y - (dimensions.y / 2), anchorPositionBeforeOffset.z };
            break;
        case pointCenter:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x  - (dimensions.x / 2), anchorPositionBeforeOffset.y - (dimensions.y / 2), anchorPositionBeforeOffset.z };
            break;
        case pointCenterRight:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x - dimensions.x, anchorPositionBeforeOffset.y - (dimensions.y / 2), anchorPositionBeforeOffset.z };
            break;
        case pointBottomLeft:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x, anchorPositionBeforeOffset.y, anchorPositionBeforeOffset.z };
            break;
        case pointBottomCenter:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x  - (dimensions.x / 2), anchorPositionBeforeOffset.y, anchorPositionBeforeOffset.z };
            break;
        case pointBottomRight:
            anchorPositionBeforeOffset = { anchorPositionBeforeOffset.x - dimensions.x, anchorPositionBeforeOffset.y, anchorPositionBeforeOffset.z };
            break;
    }
    position = anchorPositionBeforeOffset;
}