/*
    Merchant.cpp
    Zachary lineman
    3/30/22
    
    =================
    DESCRIPTION
    =================
*/

#include "Merchant.hpp"

void Merchant::overlapMerchant(std::string spriteID) {
    if(spriteID == "Main Character") {
        merchantText.hidden = false;
    }
}

void Merchant::leaveMerchant(std::string spriteID) {
    if(spriteID == "Main Character") {
        merchantText.hidden = true;
    }
}

void Merchant::setupMerchant(Scene* scene) {
    this->scenePointer = scene;
    merchantText.hidden = true;

    setCollidable(true);
    immovable = true;
    scene->loadFont("./fonts/NewHiScore.ttf", 26);
    scene->addText(&merchantText);
    scene->addSprite(this);
    scene->addCollisionArea(&merchantCollision);
}

