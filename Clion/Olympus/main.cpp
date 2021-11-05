#include <iostream>
#include <thread>
#include "Hephaestus/Hephaestus.hpp"

Hephaestus engine = Hephaestus("Hephaestus Engine");

Shader shader = engine.createShader("./Shaders/Common/shader.vert", "./Shaders/Common/shader.frag");
Sprite* mainSprite = engine.createSprite(shader, "./Images/wall.jpg");

void init() {
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

}

void destroy() {

}

void tick() {

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