/*
    GameScene.cpp
    Zachary lineman
    3/19/22

    =================
    DESCRIPTION
    =================
*/

#include "GameScene.hpp"

GameScene::GameScene(Hephaestus* _engine, Function _continueFunction) {
    engine = _engine;
    continueFunction = _continueFunction;
}

void GameScene::setupScene() {
    scene.setShouldCheckCollision(false);

    scene.setInit(std::bind(&GameScene::init, this));
    scene.setDestroy(std::bind(&GameScene::destroy, this));
    scene.setTick(std::bind(&GameScene::tick, this));
    scene.setUpdate(std::bind(&GameScene::update, this));
    scene.setRender(std::bind(&GameScene::render, this));

    scene.addKeybind(GLFW_KEY_UP, GLFW_PRESS, std::bind(&GameScene::moveCharacterUpUnit, this));
    scene.addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, std::bind(&GameScene::moveCharacterDownUnit, this));
    scene.addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, std::bind(&GameScene::moveCharacterLeftUnit, this));
    scene.addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, std::bind(&GameScene::moveCharacterRightUnit, this));

    scene.loadFont("./fonts/NewHiScore.ttf", 32);
    scene.addText(&welcText);

    scene.addCamera(&gameCamera, true);

    character.position = { engine->windowHeight() / 2, engine->windowWidth() / 2, 0};
    scene.addSprite(&character);
}


void GameScene::init() {

}

void GameScene::destroy() {

}

void GameScene::tick() {

}

void GameScene::update() {

}

void GameScene::render() {

}

void GameScene::moveCharacterUpUnit() {
    character.position.y += unitSizeInPixels;
}

void GameScene::moveCharacterDownUnit() {
    character.position.y -= unitSizeInPixels;
}

void GameScene::moveCharacterRightUnit() {
    character.position.x += unitSizeInPixels;
}

void GameScene::moveCharacterLeftUnit() {
    character.position.x -= unitSizeInPixels;
}
