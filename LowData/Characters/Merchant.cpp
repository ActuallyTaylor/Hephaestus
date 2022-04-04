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
        std::cout << "Overlapped character" << std::endl;
    
    }
}

void Merchant::setupMerchant(Scene* scene) {
    this->scenePointer = scene;
    setCollidable(true);
    immovable = true;
    scene->addSprite(this);
    scene->addCollisionArea(&merchantCollision);
}
