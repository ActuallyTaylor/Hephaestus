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

void tick() {

}

bool hitBottom = false;
void update() {
//    glm::vec3 position = mainCamera.getPosition();
//    mainCamera.setPosition({position.x, position.y , position.z});

//    mainSprite.setY(mainSprite.getY() - 0.1);
//    mainSprite.setRotation(glm::vec3(glfwGetTime() * 100, glfwGetTime()  * 100, 0));
//    secondarySprite.setRotation(glm::vec3(-(glfwGetTime() * 10), -(glfwGetTime()  * 10), 0));
}

void render() {

}

int main() {
//    vector<PhysicsSprite> sprites { };
//
//    for(int n = 0; n <= 2; n++) {
//        float x = rand() % 720;
//        float y = rand() % 720;
//
//        PhysicsSprite sprite = PhysicsSprite(shader, "./Images/circle.png", glm::vec3(x,y, 0.0));
//        sprite.setVelocity({0.0, 0.0, 0.0});
//        sprites.push_back(sprite);
//    }
//
//    for(Sprite &sprite : sprites) {
//        engine.addSprite(&sprite);
//    }
    PhysicsSprite sprite = PhysicsSprite(shader, "./Images/circle.png", glm::vec3(100,720/2 + 25 , 0.0));
    sprite.setVelocity({1.0, 0.0, 0.0});
//    sprite.mass = 1.0;
    engine.addSprite(&sprite);

    PhysicsSprite secondSprite = PhysicsSprite(shader, "./Images/circle.png", glm::vec3(720/2,720/2, 0.0));
    secondSprite.setVelocity({-1.0, 0.0, 0.0});
//    secondSprite.mass = 1.0;
    engine.addSprite(&secondSprite);

    engine.setInit(init);
    engine.setDestroy(destroy);
    engine.setTick(tick);
    engine.setUpdate(update);
    engine.setRender(render);

    engine.startWindowLoop();

    return 0;
}