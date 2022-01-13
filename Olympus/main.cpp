#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"
#include "Hephaestus/Scene/Scene.hpp"
#include "Hephaestus/Sprite/PhysicsSprite/PhysicsSprite.hpp"
#include "Hephaestus/UI/Button/Button.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");
//std::bind(&B::MyFun, this)

struct PhysicsSim {

    PhysicsSim() {
        startButton.setBackgroundColor(glm::vec4(125, 223, 100, 127.5));
        startButton.setOnClick(std::bind(&PhysicsSim::stopSpawning, this));
//    startButton.setNormalText("Hello World", "./fonts/SFNSRounded.ttf", { 0.4, 0.3, 0.4, 1.0});
        mainScene.addUIElement(&startButton);

        mainScene.addDrag(GLFW_MOUSE_BUTTON_LEFT, std::bind(&PhysicsSim::spawnOnCursor, this));
        mainScene.loadFont("./fonts/SFNSRounded.ttf");

        mainScene.addText(&fpsTextObject);

        engine.openScene(&mainScene);

        mainScene.setInit(std::bind(&PhysicsSim::init, this));
        mainScene.setDestroy(std::bind(&PhysicsSim::destroy, this));
        mainScene.setTick(std::bind(&PhysicsSim::tick, this));
        mainScene.setUpdate(std::bind(&PhysicsSim::update, this));
        mainScene.setRender(std::bind(&PhysicsSim::render, this));
    }

    Scene mainScene = Scene();
    Camera mainCamera = Camera();

    bool shouldSpawn = false;
    int numb = 0;

    Button startButton = Button("./Images/StartButton.png", glm::vec3(25,520, 0.0), glm::vec2(300,100));

    void stopSpawning() {
        if(shouldSpawn) {
            shouldSpawn = false;
            startButton.setBackgroundColor(glm::vec4(125, 223, 100, 127.5));
        } else {
            shouldSpawn = true;
            startButton.setBackgroundColor(glm::vec4(235, 96, 98, 127.5));
        }
    }

    void init() {
        const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString(GL_VERSION); // version as a string
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version supported %s\n", version);

        mainScene.addCamera(&mainCamera, true);
        mainScene.addKeybind(GLFW_KEY_A, GLFW_PRESS, std::bind(&PhysicsSim::stopSpawning, this));
    }

    void destroy() {

    }

    void tick() {
        if(numb % 5 == 0 && shouldSpawn) {
            int randDiff = rand() % 10;
            int size = 10;//(rand() % 25) + 5;
            auto* sprite = new PhysicsSprite("./Images/Smiley.png", glm::vec3(engine.windowWidth()/2 - randDiff,engine.windowHeight() - 25, 0.0), glm::vec2(size,size));
            sprite->setMass(1);

            if (!sprite->getRegistered()) {
                mainScene.addSprite(sprite);
            }
        }
        numb ++;
    }

    void update() {

    }

    Text fpsTextObject = { "Hello World", "./fonts/SFNSRounded.ttf", {10.0f, 695.0f }, { 0.5, 0.8f, 0.2f, 1.0f } };

    void render() {
        int fps = engine.getFPS();
        std::string fpsText = "FPS: " + std::to_string(fps) + ", Frametime: " + std::to_string(1000.0 / double(fps));
        fpsTextObject.text = fpsText;
    }

    void spawnOnCursor() {
        int randDiff = rand() % 10;
        int size = 10;//(rand() % 25) + 5;
        glm::vec2 cursorPosition = mainScene.getMousePosition();
        auto* sprite = new PhysicsSprite("./Images/Smiley.png", glm::vec3(cursorPosition.x - randDiff,cursorPosition.y, 0.0), glm::vec2(size,size));
        sprite->setMass(1);

        if (!sprite->getRegistered()) {
            mainScene.addSprite(sprite);
        }
    }
};

int main() {
    PhysicsSim sim = PhysicsSim();
    engine.startWindowLoop();

    return 0;
}