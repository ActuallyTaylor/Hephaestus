/*
    Image.cpp
    Zachary lineman
    3/17/22
    
    =================
    DESCRIPTION
    =================
*/

#include "Image.hpp"

Image::Image(std::string imagePath, SamplingType _sampleType, glm::vec3 _position, glm::vec2 _dimensions, glm::vec3 _rotation) {
    position = _position;
    dimensions = _dimensions;
    rotation = _rotation;
    sampleType = _sampleType;

    updateAnchorPosition();
    createTexture(imagePath, sampleType);
}

Image::Image(std::string imagePath, SamplingType _sampleType, ScreenAnchor _anchor, glm::vec3 _anchorOffset, AnchorPoint _anchorPoint, glm::vec2 _dimensions, glm::vec3 _rotation) {
    positionType = relative;
    anchorPosition = _anchor;
    relativePositionOffset = _anchorOffset;
    anchorPoint = _anchorPoint;
    dimensions = _dimensions;
    rotation = _rotation;
    sampleType = _sampleType;

    updateAnchorPosition();
    createTexture(imagePath, sampleType);
}

void Image::setImage(std::string imagePath) {
    createTexture(imagePath, sampleType);
}

void Image::setSamplingType(SamplingType _sampleType) {
    sampleType = _sampleType;
}
