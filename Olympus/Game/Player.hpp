/*
    Character.hpp
    Zachary lineman
    12/13/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_PLAYER_HPP
#define OLYMPUS_PLAYER_HPP

#include "../Hephaestus/Hephaestus.hpp"

class Player {
    Sprite sprite = Sprite("./Images/characterImage.png", {0.0,0.0,0.0}, {50, 100});

    Hephaestus *engineReference;

    static void moveRight();
public:
    glm::vec2 position = {0.0f, 0.0f};

    Player(Hephaestus *_engineReference);

    void setPosition(glm::vec2 _position);

};


#endif //OLYMPUS_PLAYER_HPP
