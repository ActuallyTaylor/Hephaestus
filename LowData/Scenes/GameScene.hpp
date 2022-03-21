/*
    GameScene.hpp
    Zachary lineman
    3/19/22
    
    =================
    DESCRIPTION
    =================
*/

#pragma once

#ifndef LOWDATA_GAMESCENE_HPP
#define LOWDATA_GAMESCENE_HPP

#include "../../Olympus/Hephaestus/Hephaestus.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"

class GameScene {
    /*
     * Hephaestus Variables
     */
    Hephaestus* engine;
    Function continueFunction;

    Camera gameCamera = Camera();

    /*
     * Hephaestus Functions
     */
    void init();
    void destroy();
    void tick();
    void update();
    void render();

    /*
     * Scene Variables
     */
    Text welcText = { "Welcome to Low Data!", "./fonts/NewHiScore.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, center, {0, 0}, pointCenter, 32};

    Sprite character = { "./images/Main_Character.png", nearest, { 10, 10, 0}, { 32, 32 }, {0, 0, 0}};

    /*
     * Scene Functions
     */
    void moveCharacterUpUnit();
    void moveCharacterDownUnit();
    void moveCharacterRightUnit();
    void moveCharacterLeftUnit();

    /*
     * Game Configuration Variables
     */
    float unitSizeInPixels = 5;
public:
    GameScene(Hephaestus* engine, Function continueFunction);

    void setupScene();

    Scene scene = Scene();
};


#endif //LOWDATA_GAMESCENE_HPP
