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


    scene.addKeybind(GLFW_KEY_W, GLFW_PRESS, std::bind(&GameScene::moveCameraUpUnit, this));
    scene.addKeybind(GLFW_KEY_S, GLFW_PRESS, std::bind(&GameScene::moveCameraDownUnit, this));
    scene.addKeybind(GLFW_KEY_A, GLFW_PRESS, std::bind(&GameScene::moveCameraLeftUnit, this));
    scene.addKeybind(GLFW_KEY_D, GLFW_PRESS, std::bind(&GameScene::moveCameraRightUnit, this));

    scene.loadFont("./fonts/NewHiScore.ttf", 18);
    scene.addText(&playerDebugText);
    scene.addText(&cameraDebugText);

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
    playerDebugText.text = std::string("x: ") + std::to_string(character.position.x) + std::string(", y: ") + std::to_string(character.position.y);
    cameraDebugText.text = std::string("x: ") + std::to_string(gameCamera.position.x) + std::string(", y: ") + std::to_string(gameCamera.position.y);

    checkIfSceneShouldMove();
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
    gameCamera.position.x -= unitSizeInPixels;
}

void GameScene::moveCameraUpUnit() {
    gameCamera.position.y += unitSizeInPixels;
}

void GameScene::moveCameraDownUnit() {
    gameCamera.position.y -= unitSizeInPixels;
}

void GameScene::moveCameraRightUnit() {
    gameCamera.position.x += unitSizeInPixels;
}

void GameScene::moveCameraLeftUnit() {
    gameCamera.position.x -= unitSizeInPixels;
}


bool hasMoved = false;
void GameScene::checkIfSceneShouldMove() {
    if (character.position.y > scene.height && !hasMoved) {
        hasMoved = true;
        printf("Move");
        gameCamera.position += glm::vec3(0, -scene.height, 0);
    }
}