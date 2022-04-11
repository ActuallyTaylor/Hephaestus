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
    flipbook.addAnimation("walking_down", { "./images/characters/Main_Character_Walk_1.png", "./images/characters/Main_Character_Walk_2.png", "./images/characters/Main_Character_Walk_3.png", "./images/characters/Main_Character_Walk_4.png" });
    flipbook.addAnimation("idle_bounce", { "./images/characters/Main_Character_Idle_1.png", "./images/characters/Main_Character_Idle_2.png" });

    this->scenePointer = scene;

    position = { scene->width / 2 - 16, scene->height / 2 - 16, 0};
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
