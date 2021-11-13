#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");

Shader shader = engine.createShader("./Shaders/Common/shader.vert", "./Shaders/Common/shader.frag");
Sprite* mainSprite = engine.addSprite(shader, "./Images/wall.jpg", glm::vec3(720/2,720/2, 0.0));
Sprite* secondarySprite = engine.addSprite(shader, "./Images/wall.jpg", glm::vec3(720/2,720/3, 0.0));

Camera* mainCamera = engine.createCamera();

void moveSpriteUp() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x, position.y - 10, position.z});
}

void moveSpriteDown() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x, position.y + 10, position.z});
}

void moveSpriteRight() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x + 10, position.y, position.z});
}

void moveSpriteLeft() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x - 10, position.y, position.z});
}

void moveSpriteRotateNegative() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x, position.y, position.z - 1});
}

void moveSpriteRotatePositive() {
    glm::vec3 position = mainCamera->getPosition();
    mainCamera->setPosition({position.x, position.y, position.z + 1});
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
//    if (!hitBottom) {
//        mainSprite->setY(mainSprite->getY() + 1);
//        if (mainSprite->getY() > 720) {
//            hitBottom = true;
//        }
//    } else {
//        mainSprite->setY(mainSprite->getY() - 1);
//        if (mainSprite->getY() < 0) {
//            hitBottom = false;
//        }
//    }

    glm::vec3 position = mainCamera->getPosition();
//    mainCamera->setPosition({position.x + 1, position.y, position.z});
    mainSprite->setRotation(glm::vec3(glfwGetTime() * 100, glfwGetTime()  * 100, 0));
    secondarySprite->setRotation(glm::vec3(glfwGetTime() * 100, glfwGetTime()  * 100, 0));
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