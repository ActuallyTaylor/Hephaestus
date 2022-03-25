/*
    GameScene.hpp
    Zachary lineman
    3/19/22
    
    =================
    DESCRIPTION
    =================
*/

#pragma once
#include <fstream>
#include <sstream>

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
    Text playerDebugText = { "x: ,y: ", "./fonts/NewHiScore.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, topLeft, {0, 0}, pointTopLeft, 18};
    Text cameraDebugText = { "x: ,y: ", "./fonts/NewHiScore.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, topLeft, {0, -18}, pointTopLeft, 18};

    Sprite character = { "./images/Main_Character.png", nearest, { 10, 10, 0}, { 32, 32 }, {0, 0, 0}};

    vector<Sprite> worldSprites { };
    /*
     * Scene Functions
     */
    void moveCharacterUpUnit();
    void moveCharacterDownUnit();
    void moveCharacterRightUnit();
    void moveCharacterLeftUnit();

    void moveCameraUpUnit();
    void moveCameraDownUnit();
    void moveCameraLeftUnit();
    void moveCameraRightUnit();

    void checkIfSceneShouldMove();

    void buildWorldFromTextDefinition(const std::string& worldPath);

    /*
     * Game Configuration Variables
     */
    float unitSizeInPixels = 2;
public:
    GameScene(Hephaestus* engine, Function continueFunction);

    void setupScene();

    Scene scene = Scene();
};


#endif //LOWDATA_GAMESCENE_HPP
