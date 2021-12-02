#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");

Shader shader = engine.createShader("./Shaders/Common/shader.vert", "./Shaders/Common/shader.frag");
Camera mainCamera = Camera();

void moveSpriteUp() {

}

void moveSpriteDown() {

}

void moveSpriteRight() {

}

void moveSpriteLeft() {

}

void moveSpriteRotateNegative() {

}

void moveSpriteRotatePositive() {

}

void init() {
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    engine.addCamera(&mainCamera);

    engine.addKeybind(GLFW_KEY_UP, GLFW_PRESS, moveSpriteUp);
    engine.addKeybind(GLFW_KEY_UP, GLFW_REPEAT, moveSpriteUp);

    engine.addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, moveSpriteDown);
    engine.addKeybind(GLFW_KEY_DOWN, GLFW_REPEAT, moveSpriteDown);

    engine.addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, moveSpriteRight);
    engine.addKeybind(GLFW_KEY_RIGHT, GLFW_REPEAT, moveSpriteRight);

    engine.addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, moveSpriteLeft);
    engine.addKeybind(GLFW_KEY_LEFT, GLFW_REPEAT, moveSpriteLeft);

    engine.addKeybind(44, GLFW_PRESS, moveSpriteRotateNegative);
    engine.addKeybind(44, GLFW_REPEAT, moveSpriteRotateNegative);

    engine.addKeybind(46, GLFW_PRESS, moveSpriteRotatePositive);
    engine.addKeybind(46, GLFW_REPEAT, moveSpriteRotatePositive);
}

void destroy() {

}

vector<PhysicsSprite> sprites { };
int numb = 0;

void tick() {
//    sprites.push_back(sprite);
    if(numb % 5 == 0) {
        int randDiff = rand() % 10;;
        auto* sprite = new PhysicsSprite(shader, "./Images/circle.png", glm::vec3(720/2 - randDiff,5, 0.0), glm::vec2(10,10));
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

}

int main() {
    engine.setInit(init);
    engine.setDestroy(destroy);
    engine.setTick(tick);
    engine.setUpdate(update);
    engine.setRender(render);

    engine.startWindowLoop();

    return 0;
}