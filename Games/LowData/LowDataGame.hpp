/*
    LowDataGame.hpp
    Zachary lineman
    3/19/22
    
    =================
    DESCRIPTION
    =================
*/

#pragma once

#ifndef LOWDATA_LOWDATAGAME_HPP
#define LOWDATA_LOWDATAGAME_HPP
#include "../../Hephaestus/Hephaestus.hpp"
#include "Scenes/MenuScene.hpp"
#include "Scenes/GameScene.hpp"

struct LowDataGame {
    Hephaestus engine = Hephaestus("Low Data", 480, 320);

    LowDataGame();

    /*
     * Scenes
     */
    // Menu Scene
    MenuScene menuScene = MenuScene(&engine, std::bind(&LowDataGame::openGameScene, this));
    void openMenu();

    // Game Scene
    GameScene gameScene = GameScene(&engine, std::bind(&LowDataGame::openMenu, this));
    void openGameScene();
};


#endif //LOWDATA_LOWDATAGAME_HPP
