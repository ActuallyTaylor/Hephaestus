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
#include "../../Olympus/Hephaestus/UI/Button/Button.hpp"

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
    Text welcomeText = { "Low Data", "./fonts/SFNSRounded.ttf", {10, 40 }, { 1.0f, 1.0f, 1.0f, 1.0f }, 32};
    Button startButton = Button(glm::vec3(25,520, 0.0), glm::vec2(300,100));

    /*
     * Scene Functions
     */
public:
    MenuScene(Hephaestus* engine);

    Scene scene = Scene();
};


#endif //LOWDATA_MENUSCENE_HPP
