/*
    Image.hpp
    Zachary lineman
    3/17/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef LOWDATA_IMAGE_HPP
#define LOWDATA_IMAGE_HPP
#include "../UIElement.hpp"

class Image: public UIElement {
public:
    explicit Image(std::string imagePath, SamplingType sampleType, glm::vec3 _position = {0.0f, 0.0f, 0.0f}, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});
    explicit Image(std::string imagePath, SamplingType _sampleType, ScreenAnchor _anchor, glm::vec3 _anchorOffset, AnchorPoint _anchorPoint, glm::vec2 _dimensions = {100.0f, 100.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f});

    void setImage(std::string imagePath);
    void setSamplingType(SamplingType sampleType);
private:
    SamplingType sampleType;
};


#endif //LOWDATA_IMAGE_HPP
