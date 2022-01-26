/*
    levelScene.cpp
    Zachary lineman
    1/12/22

    =================
    DESCRIPTION
    =================
*/

#include "mainLevelScene.hpp"

MainLevelScene::MainLevelScene(Hephaestus* _engine) {
    engine = _engine;
    for(int x = 0; x < gameFieldSize; x++) {
        for (int y = 0; y < gameFieldSize; y++) {
            gameField[x][y].alive = false;
            gameField[x][y].x = x;
            gameField[x][y].y = y;

            spriteBoard[x][y] = Sprite{ "./Images/Piece2.png", glm::vec3(x * spriteSize, y * spriteSize, 0.0), glm::vec2(spriteSize,spriteSize)};
            spriteBoard[x][y].hidden = true;
            scene.addSprite(&spriteBoard[x][y]);
        }
    }

    scene.setShouldCheckCollision(false);
    scene.loadFont("./fonts/SFNSRounded.ttf");

    using namespace std::placeholders;

    scene.addDrag(GLFW_MOUSE_BUTTON_LEFT, std::bind(&MainLevelScene::dragMouse, this));
    scene.addKeybind(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, std::bind(&MainLevelScene::clickMouse, this));
    scene.addKeybind(GLFW_KEY_SPACE, GLFW_PRESS, std::bind(&MainLevelScene::toggleUpdate, this));

    scene.addText(&simulatingText);
    scene.addText(&spriteCountObject);
    scene.addText(&fpsTextObject);

    scene.setInit(std::bind(&MainLevelScene::init, this));
    scene.setDestroy(std::bind(&MainLevelScene::destroy, this));
    scene.setTick(std::bind(&MainLevelScene::tick, this));
    scene.setUpdate(std::bind(&MainLevelScene::update, this));
    scene.setRender(std::bind(&MainLevelScene::render, this));
}


static int roundTo10(int n) {
    int a = (n / 10) * 10;
    return a;
}

int lastChangedX { -1 }, lastChangedY { -1 };

void MainLevelScene::clickMouse() {
    glm::vec2 mousePosition = scene.getMousePosition();
    glm::ivec2 boardPosition = { roundTo10(int(mousePosition.x)), roundTo10(int(mousePosition.y)) };
    glm::ivec2 arrayPosition = { boardPosition.x / spriteSize, boardPosition.y / spriteSize };

    if((arrayPosition.x < 0 || arrayPosition.x >= gameFieldSize) || (arrayPosition.y < 0 || arrayPosition.y >= gameFieldSize)) return;

    gameField[arrayPosition.x][arrayPosition.y].alive = !gameField[arrayPosition.x][arrayPosition.y].alive;
    spriteBoard[arrayPosition.x][arrayPosition.y].hidden = !gameField[arrayPosition.x][arrayPosition.y].alive;

    lastChangedX = arrayPosition.x;
    lastChangedY = arrayPosition.y;
    audioEngine.play2D("./Audio/pop.wav");
}

void MainLevelScene::dragMouse() {
    glm::vec2 mousePosition = scene.getMousePosition();
    glm::ivec2 boardPosition = { roundTo10(int(mousePosition.x)), roundTo10(int(mousePosition.y)) };
    glm::ivec2 arrayPosition = { boardPosition.x / spriteSize, boardPosition.y / spriteSize };

    if((arrayPosition.x < 0 || arrayPosition.x >= gameFieldSize) || (arrayPosition.y < 0 || arrayPosition.y >= gameFieldSize)) return;

    if (lastChangedX == arrayPosition.x && lastChangedY == arrayPosition.y) return;
    gameField[arrayPosition.x][arrayPosition.y].alive = !gameField[arrayPosition.x][arrayPosition.y].alive;
    spriteBoard[arrayPosition.x][arrayPosition.y].hidden = !gameField[arrayPosition.x][arrayPosition.y].alive;

    lastChangedX = arrayPosition.x;
    lastChangedY = arrayPosition.y;
}

void MainLevelScene::simulateGame() {
    Cell nextGameField[gameFieldSize][gameFieldSize];

    for(int x = 0; x < gameFieldSize; x++) {
        for(int y = 0;  y < gameFieldSize; y++) {
            Cell thisCell = gameField[x][y];

            int neighbors = 0;

            if ((x - 1 >= 0 && y + 1 < gameFieldSize) && gameField[x - 1][y + 1].alive) {
                neighbors += 1;
            }

            if ((x - 1 >= 0) && gameField[x - 1][y].alive) {
                neighbors += 1;
            }

            if ((x - 1 >= 0 && y - 1 >= 0) && gameField[x - 1][y - 1].alive) {
                neighbors += 1;
            }

            if ((y - 1 >= 0) && gameField[x][y - 1].alive) {
                neighbors += 1;
            }

            if ((y + 1 < gameFieldSize) && gameField[x][y + 1].alive) {
                neighbors += 1;
            }

            if ((x + 1 < gameFieldSize && y - 1 >= 0) && gameField[x + 1][y - 1].alive) {
                neighbors += 1;
            }

            if ((x + 1 < gameFieldSize) && gameField[x + 1][y].alive) {
                neighbors += 1;
            }

            if ((x + 1 < gameFieldSize && y + 1 < gameFieldSize) && gameField[x + 1][y + 1].alive) {
                neighbors += 1;
            }


            if (!thisCell.alive && neighbors == 3) {
                thisCell.alive = true;
            } else if(neighbors == 2 || neighbors == 3) {
                // Cell survives, do nothing
//                thisCell.alive = true
            } else {
                thisCell.alive = false;
            }
            nextGameField[x][y] = thisCell;
        }
    }

    for(int x = 0; x < gameFieldSize; x++) {
        for (int y = 0; y < gameFieldSize; y++) {
            gameField[x][y] = nextGameField[x][y];
            spriteBoard[x][y].hidden = !gameField[x][y].alive;
        }
    }
}

void MainLevelScene::init() {
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    scene.addCamera(&camera, true);
}

void MainLevelScene::destroy() {

}

void MainLevelScene::tick() {

}

void MainLevelScene::update() {
    if(updateCount != interval) {
        updateCount ++;
    } else {
        updateCount = 0;
        if (shouldUpdate) {
            simulateGame();
        }
    }
//    timeLeft.text = "Time until next sim: " + std::to_string(interval - updateCount);
}

void MainLevelScene::render() {
    int fps = engine->getFPS();
    std::string fpsText = "FPS: " + std::to_string(fps) + ", Frametime: " + std::to_string(1000.0 / double(fps));
    fpsTextObject.text = fpsText;

    int spriteCount = scene.getNumberOfSprites();
    std::string spriteText = "Sprites: " + std::to_string(spriteCount);
    spriteCountObject.text = spriteText;
}

void MainLevelScene::toggleUpdate() {
    shouldUpdate = !shouldUpdate;
    std::string tf = shouldUpdate ? "True" : "False";
    simulatingText.text = "Simulating: " + tf;
}