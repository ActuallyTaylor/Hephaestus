#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"
#include "Hephaestus/Window/Text/TextManager.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");

Shader shader = engine.createShader("./Shaders/Common/shader.vert", "./Shaders/Common/shader.frag");
Camera mainCamera = Camera();

vector<PhysicsSprite> sprites { };
bool shouldSpawn = false;
int numb = 0;

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

    engine.addCamera(&mainCamera);

    engine.addKeybind(GLFW_KEY_A, GLFW_PRESS, stopSpawning);
}

void destroy() {

}

void tick() {
//    sprites.push_back(sprite);
    if(numb % 5 == 0 && shouldSpawn) {
        int randDiff = rand() % 10;
        int size = 10;//(rand() % 25) + 5;
        auto* sprite = new PhysicsSprite(shader, "./Images/circle.png", glm::vec3(720/2 - randDiff,710, 0.0), glm::vec2(size,size));
        sprite->setMass(1);

        if (!sprite->getRegistered()) {
            engine.addSprite(sprite);
        }
    }
    numb ++;
}

void update() {

}

void render() {
    int fps = engine.getFPS();
    std::string fpsText = "FPS: " + std::to_string(fps) + ", Frametime: " + std::to_string(1000.0 / double(fps));
    engine.renderText(fpsText, 25.0f, 720 - 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

    int spriteCount = engine.getNumberOfSprites();
    std::string spriteText = "Sprites: " + std::to_string(spriteCount);
    engine.renderText(spriteText, 25.0f, 720 - 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
}

int main() {
//    Sprite mainSprite = Sprite(shader, "./Images/wall.jpg", glm::vec3(720/2, 0, 0));
//    engine.addSprite(&mainSprite);

    engine.loadFont("./Fonts/SFNSRounded.ttf");

    engine.setInit(init);
    engine.setDestroy(destroy);
    engine.setTick(tick);
    engine.setUpdate(update);
    engine.setRender(render);

    engine.startWindowLoop();

    return 0;
}