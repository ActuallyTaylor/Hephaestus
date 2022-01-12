/*
    levelScene.hpp
    Zachary lineman
    1/12/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef GAMEOFLIFE_MAINLEVELSCENE_HPP
#define GAMEOFLIFE_MAINLEVELSCENE_HPP

#include "./lib/hephaestus/include/Window/Sprite/Sprite.hpp"
#include "./lib/hephaestus/include/Scene/Scene.hpp"

struct Cell {
    int x { 0 };
    int y { 0 };
    bool alive = false;

    Cell() = default;
};

class MainLevelScene {

    MainLevelScene();

    const int gameFieldSize = 72;
    const int spriteSize = 10;
    Sprite spriteBoard[gameFieldSize][gameFieldSize];

    Cell gameField[gameFieldSize][gameFieldSize];

    int interval = 0;
    int updateCount = 0;
    bool shouldUpdate = false;

    Text simulatingText = { "Simulating: False", "./fonts/SFNSRounded.ttf", {10.0f, 10.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };
    Text fpsTextObject = { "Hello World", "./fonts/SFNSRounded.ttf", {10.0f, 695.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };
    Text spriteCountObject = { "Hello World", "./fonts/SFNSRounded.ttf", {10.0f, 670.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };

    Camera camera = Camera();
    Scene scene = Scene();

};


#endif //GAMEOFLIFE_MAINLEVELSCENE_HPP
