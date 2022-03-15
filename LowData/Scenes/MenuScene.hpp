/*
    MenuScene.hpp
    Zachary lineman
    3/15/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef LOWDATA_MENUSCENE_HPP
#define LOWDATA_MENUSCENE_HPP

#include "../../Olympus/Hephaestus/Hephaestus.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"

class MenuScene {
    /*
     * Hephaestus Variables
     */
    Hephaestus* engine;
    Camera camera = Camera();

    /*
     * Hephaestus Functions
     */
    void init();
    void destroy();
    void tick();
    void update();
    void render();
    void toggleUpdate();

    /*
     * Scene Variables
     */
    Text welcomeText = { "Low Data", "./fonts/SFNSRounded.ttf", {360, 360 }, { 1.0f, 1.0f, 1.0f, 1.0f }, 24};

    /*
     * Scene Functions
     */
public:
    MenuScene(Hephaestus* engine);

    Scene scene = Scene();
};


#endif //LOWDATA_MENUSCENE_HPP
