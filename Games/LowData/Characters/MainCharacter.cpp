/*
    MainCharacter.cpp
    Zachary lineman
    4/5/22
    
    =================
    DESCRIPTION
    =================
*/

#include "MainCharacter.hpp"

void MainCharacter::setupCharacter(Scene *scene) {
    flipbook.addAnimation("walking_down", {"./images/characters/Main_Character_Walk_1.png",
                                           "./images/characters/Main_Character_Walk_2.png",
                                           "./images/characters/Main_Character_Walk_3.png",
                                           "./images/characters/Main_Character_Walk_4.png"});
    flipbook.addAnimation("idle_bounce", {"./images/characters/Main_Character_Idle_1.png",
                                          "./images/characters/Main_Character_Idle_2.png"});

    this->scenePointer = scene;
    scenePointer->addUIElement(&bagImage);
    bagImage.hidden = true;

    position = {scene->width / 2 - 16, scene->height / 2 - 16, 0};
    setCollidable(true);
    scene->addSprite(this);

    scene->addKeybind(GLFW_KEY_UP, GLFW_PRESS, [this] { moveCharacterUpUnit(); });
    scene->addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, [this] { moveCharacterDownUnit(); });
    scene->addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, [this] { moveCharacterLeftUnit(); });
    scene->addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, [this] { moveCharacterRightUnit(); });

    scene->addKeybind(GLFW_KEY_UP, GLFW_RELEASE, [this] { stopMovingUp(); });
    scene->addKeybind(GLFW_KEY_DOWN, GLFW_RELEASE, [this] { stopMovingDown(); });
    scene->addKeybind(GLFW_KEY_LEFT, GLFW_RELEASE, [this] { stopMovingLeft(); });
    scene->addKeybind(GLFW_KEY_RIGHT, GLFW_RELEASE, [this] { stopMovingRight(); });

    scene->addKeybind(GLFW_KEY_B, GLFW_RELEASE, [this] { openBag(); });

    scene->addUIElement(&itemImage1);
    itemImages.push_back(&itemImage1);
    scene->addUIElement(&itemImage2);
    itemImages.push_back(&itemImage2);
    scene->addUIElement(&itemImage3);
    itemImages.push_back(&itemImage3);
    scene->addUIElement(&itemImage4);
    itemImages.push_back(&itemImage4);
    scene->addUIElement(&itemImage5);
    itemImages.push_back(&itemImage5);

    scene->addUIElement(&itemImage6);
    itemImages.push_back(&itemImage6);
    scene->addUIElement(&itemImage7);
    itemImages.push_back(&itemImage7);
    scene->addUIElement(&itemImage8);
    itemImages.push_back(&itemImage8);
    scene->addUIElement(&itemImage9);
    itemImages.push_back(&itemImage9);
    scene->addUIElement(&itemImage10);
    itemImages.push_back(&itemImage10);

    scene->addUIElement(&itemImage11);
    itemImages.push_back(&itemImage11);
    scene->addUIElement(&itemImage12);
    itemImages.push_back(&itemImage12);
    scene->addUIElement(&itemImage13);
    itemImages.push_back(&itemImage13);
    scene->addUIElement(&itemImage14);
    itemImages.push_back(&itemImage14);
    scene->addUIElement(&itemImage15);
    itemImages.push_back(&itemImage15);

    scene->addUIElement(&itemImage16);
    itemImages.push_back(&itemImage16);
    scene->addUIElement(&itemImage17);
    itemImages.push_back(&itemImage17);
    scene->addUIElement(&itemImage18);
    itemImages.push_back(&itemImage18);
    scene->addUIElement(&itemImage19);
    itemImages.push_back(&itemImage19);
    scene->addUIElement(&itemImage20);
    itemImages.push_back(&itemImage20);

    for (int x = 0; x < 20; x++) {
        bag[x] = Item(-1, "null", 0);
        itemImages[x]->hidden = true;
    }
}

void MainCharacter::openBag() {
    if (bagIsOpen) {
        bagImage.hidden = true;
        for (int x = 0; x < 20; x++) {
            itemImages[x]->hidden = true;
        }
        bagIsOpen = false;
    } else {
        bagImage.hidden = false;
        for (int x = 0; x < 20; x++) {
            itemImages[x]->hidden = false;
        }
        bagIsOpen = true;
    }
}

bool MainCharacter::isMoving() const {
    return upHeld || downHeld || rightHeld || leftHeld;
}

void MainCharacter::stopMovingUp() {
    upHeld = false;
}

void MainCharacter::stopMovingDown() {
    downHeld = false;
}

void MainCharacter::stopMovingRight() {
    rightHeld = false;
}

void MainCharacter::stopMovingLeft() {
    leftHeld = false;
}

void MainCharacter::moveCharacterUpUnit() {
    upHeld = true;
    position.y += unitSizeInPixels;
    flipbook.updateAnimation("walking_down");
}

void MainCharacter::moveCharacterDownUnit() {
    downHeld = true;
    position.y -= unitSizeInPixels;
    flipbook.updateAnimation("walking_down");
}

void MainCharacter::moveCharacterRightUnit() {
    rightHeld = true;
    position.x += unitSizeInPixels;
    flipbook.updateAnimation("walking_down");
}

void MainCharacter::moveCharacterLeftUnit() {
    leftHeld = true;
    position.x -= unitSizeInPixels;
    flipbook.updateAnimation("walking_down");
}

bool MainCharacter::pickupItem(const Item& item) {
    for (int x = 0; x < 20; x ++) {
        if (bag[x].itemID == -1 && bag[x].name == "null") { // Bag spot is empty
            bag[x] = item;
            itemImages[x]->setSamplingType(nearest);
            itemImages[x]->setImage("./Items/" + item.name + ".png");
            std::cout << "Picked up item" << std::endl;
            return true;
        }
    }
    std::cout << "Failed to pick up item" << std::endl;
    return false;
}