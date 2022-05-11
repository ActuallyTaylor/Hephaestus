/*
    MenuScene.hpp
    Zachary lineman
    3/15/22
    
    =================
    DESCRIPTION
    =================
*/
#pragma once

#ifndef LOWDATA_MENUSCENE_HPP
#define LOWDATA_MENUSCENE_HPP

#include "../../../Hephaestus/Hephaestus.hpp"
#include "../../../Hephaestus/Scene/Scene.hpp"
#include "../../../Hephaestus/UI/Image/Image.hpp"
#include "../../../Hephaestus/Sprite/PhysicsSprite/PhysicsSprite.hpp"
#include "../../../Hephaestus/Function.hpp"

class MenuScene {
    /*
     * Hephaestus Variables
     */
    Hephaestus* engine;
    Function continueFunction;

    Camera camera = Camera();

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
    Text welcomeText = { "Press Any Key To Start", "./fonts/NewHiScore.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, center, {0, 0}, pointCenter, 32};
    Image titleImage = Image("./images/Title_Artwork.png", nearest, topCenter, {0,-10,0}, pointTopCenter, {64 * 5, 15 * 5}, {0,0,0});

    /*
     * Scene Functions
     */
    void startGame();
public:
    MenuScene(Hephaestus* engine, Function continueFunction);

    void setupScene();

    Scene scene = Scene();
};


#endif //LOWDATA_MENUSCENE_HPP
