#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");

Shader shader = engine.createShader("./Shaders/Common/shader.vert", "./Shaders/Common/shader.frag");
Sprite mainSprite = Sprite(shader, "./Images/wall.jpg", glm::vec3(720/2,720/2, 0.0));
Sprite secondarySprite = Sprite(shader, "./Images/wall.jpg", glm::vec3(720/2,720/3, 0.0));

Camera mainCamera = Camera();

void moveSpriteUp()
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

    engine.addSprite(&mainSprite);
    engine.addSprite(&secondarySprite);

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

void tick() {

}

bool hitBottom = false;
void update() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x, position.y , position.z});

    mainSprite.setRotation(glm::vec3(glfwGetTime() * 100, glfwGetTime()  * 100, 0));
    secondarySprite.setRotation(glm::vec3(-(glfwGetTime() * 10), -(glfwGetTime()  * 10), 0));
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