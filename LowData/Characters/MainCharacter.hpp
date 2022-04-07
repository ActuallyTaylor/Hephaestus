/*
    MainCharacter.hpp
    Zachary lineman
    4/5/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef LOWDATA_MAINCHARACTER_HPP
#define LOWDATA_MAINCHARACTER_HPP
#include "./AnimationFlipbook.hpp"

#include "../../Olympus/Hephaestus/Sprite/Sprite.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class MainCharacter: public Sprite {
    Scene* scenePointer;
    AnimationFlipbook flipbook = AnimationFlipbook(this);

    float unitSizeInPixels = 2;

    void moveCharacterUpUnit();
    void moveCharacterDownUnit();
    void moveCharacterRightUnit();
    void moveCharacterLeftUnit();

public:
    using Sprite::Sprite;

    void setupCharacter(Scene* scene);
};


#endif //LOWDATA_MAINCHARACTER_HPP
