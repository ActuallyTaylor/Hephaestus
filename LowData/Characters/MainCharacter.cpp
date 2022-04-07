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
    flipbook.addAnimation("walking", { "./images/characters/Main_Character_Run_1.png", "./images/characters/Main_Character_Run_2.png", "./images/characters/Main_Character_Run_3.png", "./images/characters/Main_Character_Run_4.png" });

    this->scenePointer = scene;

    position = { scene->width / 2 - 16, scene->height / 2 - 16, 0};
    setCollidable(true);
    scene->addSprite(this);

    scene->addKeybind(GLFW_KEY_UP, GLFW_PRESS, [this] { moveCharacterUpUnit(); });
    scene->addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, [this] { moveCharacterDownUnit(); });
    scene->addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, [this] { moveCharacterLeftUnit(); });
    scene->addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, [this] { moveCharacterRightUnit(); });

    scene->addKeybind(GLFW_KEY_W, GLFW_PRESS, [this] { moveCharacterUpUnit(); });
    scene->addKeybind(GLFW_KEY_S, GLFW_PRESS, [this] { moveCharacterDownUnit(); });
    scene->addKeybind(GLFW_KEY_A, GLFW_PRESS, [this] { moveCharacterLeftUnit(); });
    scene->addKeybind(GLFW_KEY_D, GLFW_PRESS, [this] { moveCharacterRightUnit(); });
}

void MainCharacter::moveCharacterUpUnit() {
//    std::cout << "Character Position x: " << character.position.x << ", y: " << character.position.y << ". Camera Position x:" << gameCamera.position.x << ", y:" << gameCamera.position.y << std::endl;
    position.y += unitSizeInPixels;
    flipbook.updateAnimation("walking");
//    gameCamera.position.y -= unitSizeInPixels;
}

void MainCharacter::moveCharacterDownUnit() {
//    std::cout << "Character Position x: " << character.position.x << ", y: " << character.position.y << ". Camera Position x:" << gameCamera.position.x << ", y:" << gameCamera.position.y << std::endl;
    position.y -= unitSizeInPixels;
    flipbook.updateAnimation("walking");
//    gameCamera.position.y += unitSizeInPixels;
}

void MainCharacter::moveCharacterRightUnit() {
//    std::cout << "Character Position x: " << character.position.x << ", y: " << character.position.y << ". Camera Position x:" << gameCamera.position.x << ", y:" << gameCamera.position.y << std::endl;
    position.x += unitSizeInPixels;
    flipbook.updateAnimation("walking");
//    gameCamera.position.x -= unitSizeInPixels;
}

void MainCharacter::moveCharacterLeftUnit() {
//    std::cout << "Character Position x: " << character.position.x << ", y: " << character.position.y << ". Camera Position x:" << gameCamera.position.x << ", y:" << gameCamera.position.y << std::endl;
    position.x -= unitSizeInPixels;
    flipbook.updateAnimation("walking");
//    gameCamera.position.x += unitSizeInPixels;
}
