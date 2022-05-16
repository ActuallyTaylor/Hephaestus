#include <iostream>
#include <thread>
#include <utility>
#include "../Hephaestus/Library/json.hpp"
#include "../Hephaestus/Hephaestus.hpp"
#include "../Hephaestus/UI/Image/Image.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine", 480, 320);

using namespace std;
using json = nlohmann::json;

struct GameLoader {
    struct Game {
        string name;
        string executableName;
        string executablePath;
        string resourcePath;
        string description;
        string creator;
        string banner;
        string icon;

        Game(string name, string executableName, string executablePath, string resourcePath, string description, string creator) {
            this->name = move(name);
            this->executableName = move(executableName);
            this->executablePath = move(executablePath);
            this->resourcePath = move(resourcePath);
            this->description = move(description);
            this->creator = move(creator);

            this->banner = this->resourcePath + "banner.png";
            this->icon = this->resourcePath + "icon.png";
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
            games.emplace_back(element["name"], element["executableName"], element["executablePath"], element["resourcePath"], element["description"], element["creator"]);
        }
    }
};

struct HomeScene {
    GameLoader loader = GameLoader();

    Scene mainScene = Scene();
    Camera mainCamera = Camera();
    Text fpsTextObject = { "Olympus Launcher", "./fonts/SFNSRounded.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, topCenter, {0, -10}, pointTopCenter, 32};
    Image borderImage = Image("./UI/Border.png", SamplingType::linear, { 0, engine.windowHeight() / 2, 0}, { 0, 0});
    Image backgroundImage = Image("./UI/Background.png", SamplingType::linear, center, { 0, 0, -1 }, pointCenter, {engine.windowWidth(), engine.windowHeight()});


    int imageWidth = 1920/7;
    int imageHeight = 1080/7;
    int selectedIndex { 0 };
    vector<Image> images { };

    HomeScene() {
        mainScene.setPhysicsEnabled(false);
        mainScene.setCollisionsEnabled(false);

        mainScene.loadFont("./fonts/SFNSRounded.ttf", 32);
        backgroundImage = Image("./UI/Background.png", SamplingType::linear, center, { 0, 0, -1 }, pointCenter, {engine.windowWidth(), engine.windowHeight()});
        mainScene.addUIElement(&backgroundImage);

        borderImage = Image("./UI/Border.png", SamplingType::linear, center, { 0, 0, 0 }, pointCenter, {imageWidth, imageHeight});

        mainScene.addText(&fpsTextObject);

        mainScene.setInit([this] { init(); });
        mainScene.setDestroy([this] { destroy(); });
        mainScene.setTick([this] { tick(); });
        mainScene.setUpdate([this] { update(); });
        mainScene.setRender([this] { render(); });
        mainScene.setScreenSizeChanged([this] { sizeChanged(); });

        mainScene.addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, [this] { right(); }, false);
        mainScene.addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, [this] { left(); }, false);
        mainScene.addKeybind(GLFW_KEY_UP, GLFW_PRESS, [this] { up(); }, false);
        mainScene.addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, [this] { down(); }, false);
        mainScene.addKeybind(GLFW_KEY_ENTER, GLFW_PRESS, [this] { enter(); }, false);

    }

    void init() {
        const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString(GL_VERSION); // version as a string
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version supported %s\n", version);

        mainScene.addCamera(&mainCamera, true);
        int x = 0;

        for(GameLoader::Game& game: loader.games) {
            Image gameImage = Image(game.banner, SamplingType::linear, center, { x, 0, 0 }, pointCenter, {imageWidth, imageHeight});
            images.emplace_back(gameImage);
            x += imageWidth;
        }

        for(Image& image: images) {
            mainScene.addUIElement(&image);
        }

        mainScene.addUIElement(&borderImage);
    }

    void destroy() {

    }

    void tick() {

    }

    void update() {

    }

    void render() {

    }

    void right() {
        if (selectedIndex < loader.games.size() - 1) {
            selectedIndex += 1;
            for(Image& image: images) {
                image.relativePositionOffset.x -= imageWidth;
            }
        }
    }

    void left() {
        if (selectedIndex > 0) {
            selectedIndex -= 1;
            for(Image& image: images) {
                image.relativePositionOffset.x += imageWidth;
            }
        }
    }

    void up() {

    }

    void down() {

    }

    void enter() {
        string executionPath = "cd " + loader.games[selectedIndex].executablePath + " && ./" +  loader.games[selectedIndex].executableName;
        system(executionPath.c_str());
    }

    void sizeChanged() {
        backgroundImage.dimensions = {engine.windowWidth(), engine.windowHeight()};

    }
};

int main() {
    HomeScene homeScene = HomeScene();
    engine.openScene(&homeScene.mainScene);
    engine.startWindowLoop();
    
    return 0;
}