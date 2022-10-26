#include <iostream>
#include <thread>
#include <Hephaestus/Hephaestus.hpp>
#include <Hephaestus/Scene/Scene.hpp>
#include <Hephaestus/Sprite/PhysicsSprite.hpp>
#include <Hephaestus/UI/Button/Button.hpp>
#include <Hephaestus/AudioEngine/AudioEngine.hpp>

Hephaestus engine = Hephaestus("Physics Demo", 480, 320);

struct PhysicsSim {
    Scene mainScene = Scene();
    Camera mainCamera = Camera();
    Text fpsTextObject = { "Hello World", "./Fonts/SFNSRounded.ttf", { 0.5, 0.8f, 0.2f, 1.0f }, ScreenAnchor::topLeft, { 0 , 0 }, AnchorPoint::pointTopLeft};

    bool shouldSpawn = false;
    int numb = 0;

    PhysicsSim() {
        mainScene.setPhysicsEnabled(true);
        mainScene.setCollisionsEnabled(true);

        mainScene.addDrag(GLFW_MOUSE_BUTTON_LEFT, [this] { spawnOnCursor(); });
        mainScene.loadFont("./Fonts/SFNSRounded.ttf");

        mainScene.addText(&fpsTextObject);
        mainScene.setInit([this] { init(); });
        mainScene.setDestroy([this] { destroy(); });
        mainScene.setTick([this] { tick(); });
        mainScene.setUpdate([this] { update(); });
        mainScene.setRender([this] { render(); });
    }

    void stopSpawning() {
        if(shouldSpawn) {
            shouldSpawn = false;
        } else {
            shouldSpawn = true;
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
            auto* sprite = new PhysicsSprite("Object " + to_string(numb), "./Images/Smiley.png", nearest, glm::vec3(engine.windowWidth()/2 - randDiff,engine.windowHeight() - 25, 0.0), glm::vec2(size,size));
            sprite->setMass(1);

            if (!sprite->getRegistered()) {
                mainScene.addSprite(sprite);
            }
        }
        numb ++;
    }

    void update() {

    }

    void render() {
        int fps = engine.getFPS();
        std::string fpsText = "FPS: " + std::to_string(fps) + ", Frametime: " + std::to_string(1000.0 / double(fps));
        fpsTextObject.text = fpsText;
    }

    void spawnOnCursor() {
        int randDiff = rand() % 10;
        int size = 10;//(rand() % 25) + 5;
        glm::vec2 cursorPosition = mainScene.getMousePosition();
        auto* sprite = new PhysicsSprite("Object " + to_string(generateID()), "./Images/Smiley.png", nearest, glm::vec3(cursorPosition.x - randDiff,cursorPosition.y, 0.0), glm::vec2(size,size));
        sprite->setMass(1);

        if (!sprite->getRegistered()) {
            mainScene.addSprite(sprite);
        }
    }
};

int main() {
    PhysicsSim sim = PhysicsSim();
    engine.openScene(&sim.mainScene);
    engine.startWindowLoop();

    return 0;
}