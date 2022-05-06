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
#include "../Items/Item.hpp"

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

    // MARK: Bag
    Image bagImage = Image("./images/Bag.png", nearest, center, {0,0,0}, pointCenter, {320, 280});
    vector<Image*> itemImages { };

    // Bag Items, looks ugly but works for now
    Image itemImage1 = Image("./Hephaestus/blank.png", nearest, center, {-118,96,0}, pointCenter, { 38, 38 });
    Image itemImage2 = Image("./Hephaestus/blank.png", nearest, center, {-59,96,0}, pointCenter, { 38, 38 });
    Image itemImage3 = Image("./Hephaestus/blank.png", nearest, center, {0,96,0}, pointCenter, { 38, 38 });
    Image itemImage4 = Image("./Hephaestus/blank.png", nearest, center, {59,96,0}, pointCenter, { 38, 38 });
    Image itemImage5 = Image("./Hephaestus/blank.png", nearest, center, {118,96,0}, pointCenter, { 38, 38 });

    Image itemImage6 = Image("./Hephaestus/blank.png", nearest, center, {-118,32,0}, pointCenter, { 38, 38 });
    Image itemImage7 = Image("./Hephaestus/blank.png", nearest, center, {-59,32,0}, pointCenter, { 38, 38 });
    Image itemImage8 = Image("./Hephaestus/blank.png", nearest, center, {0,32,0}, pointCenter, { 38, 38 });
    Image itemImage9 = Image("./Hephaestus/blank.png", nearest, center, {59,32,0}, pointCenter, { 38, 38 });
    Image itemImage10 = Image("./Hephaestus/blank.png", nearest, center, {118,32,0}, pointCenter, { 38, 38 });

    Image itemImage11 = Image("./Hephaestus/blank.png", nearest, center, {-118,-32,0}, pointCenter, { 38, 38 });
    Image itemImage12 = Image("./Hephaestus/blank.png", nearest, center, {-59,-32,0}, pointCenter, { 38, 38 });
    Image itemImage13 = Image("./Hephaestus/blank.png", nearest, center, {0,-32,0}, pointCenter, { 38, 38 });
    Image itemImage14 = Image("./Hephaestus/blank.png", nearest, center, {59,-32,0}, pointCenter, { 38, 38 });
    Image itemImage15 = Image("./Hephaestus/blank.png", nearest, center, {118,-32,0}, pointCenter, { 38, 38 });

    Image itemImage16 = Image("./Hephaestus/blank.png", nearest, center, {-118,-96,0}, pointCenter, { 38, 38 });
    Image itemImage17 = Image("./Hephaestus/blank.png", nearest, center, {-59,-96,0}, pointCenter, { 38, 38 });
    Image itemImage18 = Image("./Hephaestus/blank.png", nearest, center, {0,-96,0}, pointCenter, { 38, 38 });
    Image itemImage19 = Image("./Hephaestus/blank.png", nearest, center, {59,-96,0}, pointCenter, { 38, 38 });
    Image itemImage20 = Image("./Hephaestus/blank.png", nearest, center, {118,-96,0}, pointCenter, { 38, 38 });

    bool bagIsOpen = false;
    void openBag();

    int bagColumns = 5;
    int bagRows = 4;

    Item bag [20];

public:
    using Sprite::Sprite;

    bool pickupItem(const Item& item);
    void setupCharacter(Scene* scene);

    bool isMoving() const;
    AnimationFlipbook flipbook = AnimationFlipbook(this);
};


#endif //LOWDATA_MAINCHARACTER_HPP
