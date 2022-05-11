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

#include "../../../Hephaestus/Hephaestus.hpp"
#include "../../../Hephaestus/Scene/Scene.hpp"
#include "../Characters/Merchant.hpp"
#include "../Characters/MainCharacter.hpp"
#include "../Items/DroppedItem.hpp"
#include "../Environment/EncounterSpace.hpp"

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

    MainCharacter mainCharacter = { "Main Character",  "./images/Main_Character.png", nearest, { 10, 10, 0}, { 32, 32 }, {0, 0, 0}};
    Merchant merchant = { "Merchant", "./images/Merchant.png", nearest, { 10, 10, 0}, { 32, 32 }, {0, 0, 0}};
    EncounterSpace space = EncounterSpace(1.0,EncounterSpace::Grass, { 100, 100, 0 }, [this](auto && PH1) { overlappedEncounterSpace(std::forward<decltype(PH1)>(PH1)); });

    vector<Sprite> worldSprites { };
    vector<DroppedItem> droppedItems { };
    bool isPickingUp = false;

    /*
     * Scene Functions
    */
    void buildWorldFromTextDefinition(const std::string& worldPath);
    void droppedItemOverlapped(Item* item, DroppedItem* dItem);
    void overlappedEncounterSpace(EncounterSpace* encounterSpace);

    /*
     * Game Configuration Variables
     */
    int characterCenteringX { };
    int characterCenteringY { };

public:
    GameScene(Hephaestus* engine, Function continueFunction);

    void setupScene();

    Scene scene = Scene();
};


#endif //LOWDATA_GAMESCENE_HPP
