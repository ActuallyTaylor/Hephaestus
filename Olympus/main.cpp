#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");

Shader shader = engine.createShader("./Shaders/Common/shader.vert", "./Shaders/Common/shader.frag");
Sprite* mainSprite = engine.addSprite(shader, "./Images/wall.jpg", glm::vec3(720/2,0.0, 0.0));

void moveSpriteUp() {
    mainSprite->setY(mainSprite->getY() - 10);
}

void moveSpriteDown() {
    mainSprite->setY(mainSprite->getY() + 10);
}

void moveSpriteRight() {
    mainSprite->setX(mainSprite->getX() + 10);
}

void moveSpriteLeft() {
    mainSprite->setX(mainSprite->getX() - 10);
}

void init() {
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    engine.addKeybind(GLFW_KEY_UP, GLFW_PRESS, moveSpriteUp);
    engine.addKeybind(GLFW_KEY_UP, GLFW_REPEAT, moveSpriteUp);

    engine.addKeybind(GLFW_KEY_DOWN, GLFW_PRESS, moveSpriteDown);
    engine.addKeybind(GLFW_KEY_DOWN, GLFW_REPEAT, moveSpriteDown);

    engine.addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, moveSpriteRight);
    engine.addKeybind(GLFW_KEY_RIGHT, GLFW_REPEAT, moveSpriteRight);

    engine.addKeybind(GLFW_KEY_LEFT, GLFW_PRESS, moveSpriteLeft);
    engine.addKeybind(GLFW_KEY_LEFT, GLFW_REPEAT, moveSpriteLeft);
}

void destroy() {

}

void tick() {

}

bool hitBottom = false;
void update() {
    if (!hitBottom) {
        mainSprite->setY(mainSprite->getY() + 1);
        if (mainSprite->getY() > 720) {
            hitBottom = true;
        }
    } else {
        mainSprite->setY(mainSprite->getY() - 1);
        if (mainSprite->getY() < 0) {
            hitBottom = false;
        }
    }

    mainSprite->setRotation(glm::vec3(glfwGetTime() * 100, glfwGetTime()  * 100, 0));
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