//
//  SpriteRenderer.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/27/21.
//

#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Shader shader, int width, int height) {
    Vertex vertices[] = {
        Vertex(vec3(0.5f,  0.5f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
        Vertex(vec3(0.5f, -0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
        Vertex(vec3(-0.5f,  0.5f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
        Vertex(vec3(0.5f, -0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
        Vertex(vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        Vertex(vec3(-0.5f,  0.5f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
    };

    vector<Vertex> holdVertices = {};
    for(int i = 0; i < 6; i++) {
        holdVertices.push_back(vertices[i]);
    }
    
    mat4 projection = ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    shader.use();
    shader.setInteger("image", 0);
    shader.setMatrix4("projection", projection);

    geometryBuffer = GeometryBuffer("sprite", holdVertices, shader, "./resources/missing.jpg");
}

void SpriteRenderer::registerSprite(string id, string texturePath, vec2 position, vec2 size, float rotate, vec3 color) {
    sprites.push_back(Sprite(id, texturePath, position, size, rotate, color));
}

void SpriteRenderer::drawAllSprites()  {
    for (Sprite sprite : sprites) {
        mat4 model = mat4(1.0f);
        model = translate(model, vec3(sprite.position, 0.0f));

        model = translate(model, vec3(0.5f * sprite.size.x, 0.5f * sprite.size.y, 0.0f));
        model = glm::rotate(model, radians(sprite.rotate), vec3(0.0f, 0.0f, 1.0f));
        model = translate(model, vec3(-0.5f * sprite.size.x, -0.5f * sprite.size.y, 0.0f));

        model = scale(model, vec3(sprite.size, 1.0f));

        geometryBuffer.shader.setMatrix4("model", model);
        geometryBuffer.shader.setVector3f("spriteColor", sprite.color);
        geometryBuffer.draw();
    }
}
