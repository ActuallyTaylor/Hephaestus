#include <iostream>
#include "./lib/hephaestus/include/Hephaestus.hpp"
#include <vector>

Hephaestus engine = Hephaestus("Conways game of life");
Camera mainCamera = Camera();

glm::ivec2 movement { 0.0, 0.0};
const int gameFieldSize = 72;
const int spriteSize = 10;
Sprite spriteBoard[gameFieldSize][gameFieldSize];
int interval = 0;
int updateCount = 0;
bool shouldUpdate = false;

Text simulatingText = { "Simulating: False", "./Fonts/SFNSRounded.ttf", {10.0f, 10.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };
Text fpsTextObject = { "Hello World", "./Fonts/SFNSRounded.ttf", {10.0f, 695.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };
Text spriteCountObject = { "Hello World", "./Fonts/SFNSRounded.ttf", {10.0f, 670.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };

struct Cell {
    int x { 0 };
    int y { 0 };
    int lastChangedTime { 0 };

    bool alive = false;

    Cell() = default;

    void updatePosition(glm::vec2 boardPosition) const {
        spriteBoard[x][y].setPosition({boardPosition, 0.0});
    }

    void updateDisplay() const {
        spriteBoard[x][y].hidden = !alive;
    }
};

Cell gameField[gameFieldSize][gameFieldSize];

static int roundTo10(int n) {
    int a = (n / 10) * 10;
    return a;
}

int lastChangedX { -1 }, lastChangedY { -1 };
void clickMouse() {
    glm::vec2 mousePosition = engine.getMousePosition();
    glm::ivec2 boardPosition = { roundTo10(int(mousePosition.x)) + movement.x, roundTo10(int(mousePosition.y)) + movement.y};
    glm::ivec2 arrayPosition = { boardPosition.x / spriteSize, boardPosition.y / spriteSize };

    printf("Board Position: %s - Movement: %s\n", glm::to_string(boardPosition).c_str(), glm::to_string(movement).c_str());

    if((arrayPosition.x < 0 || arrayPosition.x >= gameFieldSize) || (arrayPosition.y < 0 || arrayPosition.y >= gameFieldSize)) return;

    if(!gameField[arrayPosition.x][arrayPosition.y].alive) {
        gameField[arrayPosition.x][arrayPosition.y].alive = true;
        gameField[arrayPosition.x][arrayPosition.y].updateDisplay();
    } else {
        gameField[arrayPosition.x][arrayPosition.y].alive = false;
        gameField[arrayPosition.x][arrayPosition.y].updateDisplay();
    }
    gameField[arrayPosition.x][arrayPosition.y].lastChangedTime = glfwGetTime();
    lastChangedX = arrayPosition.x;
    lastChangedY = arrayPosition.y;
}

void dragMouse() {
    glm::vec2 mousePosition = engine.getMousePosition();
    glm::ivec2 boardPosition = { roundTo10(int(mousePosition.x)) + movement.x, roundTo10(int(mousePosition.y)) + movement.y};
    glm::ivec2 arrayPosition = { boardPosition.x / spriteSize, boardPosition.y / spriteSize };

    if((arrayPosition.x < 0 || arrayPosition.x >= gameFieldSize) || (arrayPosition.y < 0 || arrayPosition.y >= gameFieldSize)) return;

    if (lastChangedX == arrayPosition.x && lastChangedY == arrayPosition.y) return;
    if(!gameField[arrayPosition.x][arrayPosition.y].alive) {
        gameField[arrayPosition.x][arrayPosition.y].alive = true;
        gameField[arrayPosition.x][arrayPosition.y].updateDisplay();
    } else {
        gameField[arrayPosition.x][arrayPosition.y].alive = false;
        gameField[arrayPosition.x][arrayPosition.y].updateDisplay();
    }
    lastChangedX = arrayPosition.x;
    lastChangedY = arrayPosition.y;
}

void simulateGame() {
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
            gameField[x][y].updateDisplay();
        }
    }
}

void init() {
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    engine.addCamera(&mainCamera);
}

void destroy() {

}

void tick() {

}

void update() {
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


void render() {
    int fps = engine.getFPS();
    std::string fpsText = "FPS: " + std::to_string(fps) + ", Frametime: " + std::to_string(1000.0 / double(fps));
    fpsTextObject.text = fpsText;

    int spriteCount = engine.getNumberOfSprites();
    std::string spriteText = "Sprites: " + std::to_string(spriteCount);
    spriteCountObject.text = spriteText;
}

void toggleUpdate() {
    shouldUpdate = !shouldUpdate;
    std::string tf = shouldUpdate ? "True" : "False";
    simulatingText.text = "Simulating: " + tf;
}

void moveRight() {
    mainCamera.position = { mainCamera.position.x + 10, mainCamera.position.y, mainCamera.position.z };
    movement.x -= 10;
}

void moveLeft() {
    mainCamera.position = { mainCamera.position.x - 10, mainCamera.position.y, mainCamera.position.z };
    movement.x += 10;
}

void moveUp() {
    mainCamera.position = { mainCamera.position.x, mainCamera.position.y + 10, mainCamera.position.z };
    movement.y -= 10;
}

void moveDown() {
    mainCamera.position = { mainCamera.position.x, mainCamera.position.y - 10, mainCamera.position.z };
    movement.y += 10;
}

int main() {
    for(int x = 0; x < gameFieldSize; x++) {
        for (int y = 0; y < gameFieldSize; y++) {
            gameField[x][y].alive = false;
            gameField[x][y].x = x;
            gameField[x][y].y = y;

            spriteBoard[x][y] = Sprite{ "./Images/Piece2.png", glm::vec3(x * spriteSize, y * spriteSize, 0.0), glm::vec2(spriteSize,spriteSize)};
            spriteBoard[x][y].hidden = true;
            engine.addSprite(&spriteBoard[x][y]);
        }
    }

    engine.setWindowShouldCheckCollision(false);
    engine.loadFont("./Fonts/SFNSRounded.ttf");

    engine.addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, moveRight);
    engine.addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, moveLeft);
    engine.addKeybind(GLFW_KEY_UP, GLFW_PRESS, moveUp);
    engine.addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, moveDown);


    engine.addDrag(GLFW_MOUSE_BUTTON_LEFT, dragMouse);
    engine.addKeybind(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, clickMouse);
    engine.addKeybind(GLFW_KEY_SPACE, GLFW_PRESS, toggleUpdate);

    engine.addText(&simulatingText);
    engine.addText(&spriteCountObject);
    engine.addText(&fpsTextObject);

    engine.setInit(init);
    engine.setDestroy(destroy);
    engine.setTick(tick);
    engine.setUpdate(update);
    engine.setRender(render);

    engine.startWindowLoop();

    return 0;
}