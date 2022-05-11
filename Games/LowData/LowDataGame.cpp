/*
    LowDataGame.cpp
    Zachary lineman
    3/19/22
    
    =================
    DESCRIPTION
    =================
*/

#include "LowDataGame.hpp"

LowDataGame::LowDataGame() {
    openMenu();
    engine.startWindowLoop();
}

void LowDataGame::openMenu() {
    menuScene.setupScene();
    engine.openScene(&menuScene.scene);
}

void LowDataGame::openGameScene() {
    gameScene.setupScene();
    engine.openScene(&gameScene.scene);
}