/*
    AnimationFlipbook.cpp
    Zachary lineman
    4/5/22
    
    =================
    DESCRIPTION
    =================
*/

#include "AnimationFlipbook.hpp"

#include <utility>

AnimationFlipbook::AnimationFlipbook(Sprite* sprite) {
    this->targetSprite = sprite;
}

AnimationFlipbook::AnimationFlipbook(Sprite* sprite, std::map<std::string, std::vector<std::string>> mappedAnimations) {
    this->targetSprite = sprite;
    this->mappedAnimations = std::move(mappedAnimations);
}

void AnimationFlipbook::addAnimation(std::string identifier, std::vector<std::string> animationFrames) {
    auto pair = std::pair<std::string, std::vector<std::string>>(identifier, animationFrames);
    mappedAnimations.insert(pair);
}

void AnimationFlipbook::updateAnimation(std::string type) {
    if(animationFPS > animationFPSCount) {
        animationFPSCount ++;
        return;
    }
    animationFPSCount = 0;

    if(type != currentAnimationIdentifier) {
        currentAnimationIdentifier = type;
        currentAnimationProgress = 0;
    } else {
        if (currentAnimationProgress < mappedAnimations[type].size() - 1) {
            currentAnimationProgress ++;
        } else {
            currentAnimationProgress = 0;
        }
    }

    vector<std::string> frames = mappedAnimations[type];
    std::string frame = frames[currentAnimationProgress];
    targetSprite->setTexture(frame);
}