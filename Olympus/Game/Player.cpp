/*
    Character.cpp
    Zachary lineman
    12/13/21
    
    =================
    DESCRIPTION
    =================
*/

#include "Player.hpp"

Player *playerSelf;

void Player::moveRight() {
    playerSelf->setPosition({playerSelf->position.x + 1, playerSelf->position.y});
}

Player::Player(Hephaestus *_engineReference) {
    engineReference = _engineReference;
    engineReference->addSprite(&sprite);
    engineReference->addKeybind(GLFW_KEY_RIGHT, GLFW_PRESS, moveRight);
    engineReference->addKeybind(GLFW_KEY_RIGHT, GLFW_REPEAT, moveRight);

    playerSelf = this;
}

void Player::setPosition(glm::vec2 _position) {
    position = _position;
    sprite.position = {position, 0.0};
}
