#include <iostream>
#include <thread>
#include <utility>
#include "../Hephaestus/Library/json.hpp"
#include "../Hephaestus/Hephaestus.hpp"

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
            this->name = std::move(name);
            this->executablePath= std::move(executablePath);
            this->resourcePath = std::move(resourcePath);
            this->description = std::move(description);
            this->creator = std::move(creator);
        }
    };

    json j;
    vector<Game> games { };

    GameLoader() {
        reloadGames();
    }

    void reloadGames() {
        ifstream i("./directory.json");
        i >> j;

        games.clear();
        // range-based for
        for (auto& element : j["Games"]) {
            games.emplace_back(element["name"], element["executablePath"], element["resourcePath"], element["description"], element["creator"]);
        }
    }

    string getGameIcon(Game& game) {
        return game.resourcePath + "icon.png";
    }

    string getGameBanner(Game& game) {
        return game.resourcePath + "banner.png";
    }
};

struct HomeScene {
    GameLoader loader = GameLoader();

    Scene mainScene = Scene();
    Camera mainCamera = Camera();
    Text fpsTextObject = { "Olympus Launcher", "./fonts/SFNSRounded.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, topCenter, {0, -10}, pointTopCenter, 32};

    HomeScene() {
        mainScene.setPhysicsEnabled(false);
        mainScene.setCollisionsEnabled(false);

        mainScene.loadFont("./fonts/SFNSRounded.ttf", 32);

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
        for(GameLoader::Game& game: loader.games) {
            cout << game.name << endl;
        }
    }
};

int main() {
    HomeScene homeScene = HomeScene();
    engine.openScene(&homeScene.mainScene);
    engine.startWindowLoop();
    
    return 0;
}