#include <iostream>
#include <thread>
#include "../Hephaestus/Library/json.hpp"
#include "../Hephaestus/Hephaestus.hpp"
#include "../Hephaestus/Scene/Scene.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine", 480, 320);

using namespace std;
using json = nlohmann::json;

struct GameLoader {
    struct Game {
        string name;
        string executablePath;
        string resourcePath;
        string description;
        string creator;

        Game(string name, string executablePath, string resourcePath, string description, string creator) {
            this->name = name;
            this->executablePath= executablePath;
            this->resourcePath = resourcePath;
            this->description = description;
            this->creator = creator;
        }
    };

    json j;

    GameLoader() {
        string test;
        ifstream i("./directory.json");
        i >> test;
        cout << test << endl;

        i >> j;

        // range-based for
        for (auto& element : j["Games"]) {
            std::cout << element << '\n';
        }
    }
};

struct HomeScene {
    GameLoader loader = GameLoader();

    Scene mainScene = Scene();
    Camera mainCamera = Camera();
    Text fpsTextObject = { "Olympus Launcher", "./Fonts/SFNSRounded.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, topCenter, {0, -10}, pointTopCenter, 32};

    HomeScene() {
        mainScene.setPhysicsEnabled(false);
        mainScene.setCollisionsEnabled(false);

        mainScene.loadFont("./Fonts/SFNSRounded.ttf", 32);

        mainScene.addText(&fpsTextObject);
        mainScene.setInit([this] { init(); });
        mainScene.setDestroy([this] { destroy(); });
        mainScene.setTick([this] { tick(); });
        mainScene.setUpdate([this] { update(); });
        mainScene.setRender([this] { render(); });
    }

    void init() {
        const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString(GL_VERSION); // version as a string
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version supported %s\n", version);

        mainScene.addCamera(&mainCamera, true);
    }

    void destroy() {

    }

    void tick() {

    }

    void update() {

    }

    void render() {
    }
};

int main() {
    HomeScene homeScene = HomeScene();
    engine.openScene(&homeScene.mainScene);
    engine.startWindowLoop();
    
    return 0;
}