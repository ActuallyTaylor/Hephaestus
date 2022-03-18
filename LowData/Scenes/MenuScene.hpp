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
#include "../../Olympus/Hephaestus/UI/Image/Image.hpp"
#include "../../Olympus/Hephaestus/HephaestusEnums.hpp"

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

    /*
     * Scene Variables
     */
//    Text welcomeText = { "Low Data", "./fonts/SFNSRounded.ttf", {10, 40 }, { 1.0f, 1.0f, 1.0f, 1.0f }, 32};
    Image titleImage = Image("./images/Title_Artwork.png", nearest, {0, 0, 0}, {64 * 10, 15 * 10}, {0,0,0});

    /*
     * Scene Functions
     */
public:
    MenuScene(Hephaestus* engine);

    Scene scene = Scene();
};


#endif //LOWDATA_MENUSCENE_HPP
