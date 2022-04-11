/*
    AnimationFlipbook.hpp
    Zachary lineman
    4/5/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef LOWDATA_ANIMATIONFLIPBOOK_HPP
#define LOWDATA_ANIMATIONFLIPBOOK_HPP
#include <map>
#include "../../Olympus/Hephaestus/Sprite/Sprite.hpp"

class AnimationFlipbook {
    std::map<std::string, std::vector<std::string>> mappedAnimations { };
    std::string currentAnimationIdentifier { 0 };
    int currentAnimationProgress { 0 };

    Sprite* targetSprite;
public:
    AnimationFlipbook(Sprite* targetSprite);
    AnimationFlipbook(Sprite* targetSprite, std::map<std::string, std::vector<std::string>> mappedAnimations);

    int animationFPS = 12;
    int animationFPSCount = 0;
    void addAnimation(std::string identifier, std::vector<std::string> animationFrames);
    void updateAnimation(std::string type);
};

#endif //LOWDATA_ANIMATIONFLIPBOOK_HPP
