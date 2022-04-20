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
#include "../../Olympus/Hephaestus/UI/Image/Image.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class MainCharacter: public Sprite {
    Scene* scenePointer;
    Image bagImage = Image("./images/Bag.jpeg", nearest, center, {0,0,0}, pointCenter, {160, 140});

    float unitSizeInPixels = 2;

    bool upHeld = false;
    void moveCharacterUpUnit();
    bool downHeld = false;
    void moveCharacterDownUnit();
    bool rightHeld = false;
    void moveCharacterRightUnit();
    bool leftHeld = false;
    void moveCharacterLeftUnit();

    void stopMovingUp();
    void stopMovingDown();
    void stopMovingRight();
    void stopMovingLeft();

    bool bagIsOpen = false;
    void openBag();
public:
    using Sprite::Sprite;

    void setupCharacter(Scene* scene);

    bool isMoving() const;
    AnimationFlipbook flipbook = AnimationFlipbook(this);
};


#endif //LOWDATA_MAINCHARACTER_HPP
