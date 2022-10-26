/*
    MenuScene.cpp
    Zachary lineman
    3/15/22
    
    =================
    DESCRIPTION
    =================
*/

#include "MenuScene.hpp"
#include <Hephaestus/HephaestusUtility.hpp>

MenuScene::MenuScene(Hephaestus* _engine, Function _continueFunction) {
    engine = _engine;
    continueFunction = _continueFunction;
}

void MenuScene::setupScene() {
    scene.setPhysicsEnabled(false);

    using namespace std::placeholders;
    scene.setInit(std::bind(&MenuScene::init, this));
    scene.setDestroy(std::bind(&MenuScene::destroy, this));
    scene.setTick(std::bind(&MenuScene::tick, this));
    scene.setUpdate(std::bind(&MenuScene::update, this));
    scene.setRender(std::bind(&MenuScene::render, this));

    scene.loadFont("./fonts/NewHiScore.ttf", 32);
    scene.addText(&welcomeText);
    scene.addUIElement(&titleImage);

    scene.addCamera(&camera, true);
    scene.addKeybind(HEPHAESTUS_ANY_KEY, GLFW_PRESS, std::bind(&MenuScene::startGame, this));
}

void MenuScene::init() {

}

void MenuScene::destroy() {

}

void MenuScene::tick() {

}

void MenuScene::update() {

}

void MenuScene::render() {

}

void MenuScene::startGame() {
    continueFunction();
}