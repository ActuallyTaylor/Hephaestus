/*
    MenuScene.cpp
    Zachary lineman
    3/15/22
    
    =================
    DESCRIPTION
    =================
*/

#include "MenuScene.hpp"


MenuScene::MenuScene(Hephaestus* _engine) {
    engine = _engine;

    scene.setShouldCheckCollision(false);

    using namespace std::placeholders;
    scene.setInit(std::bind(&MenuScene::init, this));
    scene.setDestroy(std::bind(&MenuScene::destroy, this));
    scene.setTick(std::bind(&MenuScene::tick, this));
    scene.setUpdate(std::bind(&MenuScene::update, this));
    scene.setRender(std::bind(&MenuScene::render, this));

    startButton.positionType = UIElement::relative;
    startButton.setAnchorPosition(UIElement::center);
    startButton.setBackgroundColor(glm::vec4(125, 223, 100, 127.5));
    startButton.setAnchorPoint(UIElement::pointCenter);

    scene.addUIElement(&startButton);

    welcomeText.positionType = Text::relative;
    welcomeText.setAnchorPoint(Text::pointCenter);
    welcomeText.setAnchorPosition(Text::center);
    scene.loadFont("./fonts/SFNSRounded.ttf", 32);
    scene.addText(&welcomeText);
}

void MenuScene::init() {
    scene.addCamera(&camera, true);
}

void MenuScene::destroy() {

}

void MenuScene::tick() {

}

void MenuScene::update() {

}

void MenuScene::render() {

}