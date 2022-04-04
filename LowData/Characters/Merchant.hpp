/*
    Merchant.hpp
    Zachary lineman
    3/30/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef LOWDATA_MERCHANT_HPP
#define LOWDATA_MERCHANT_HPP
#include "../../Olympus/Hephaestus/Sprite/Sprite.hpp"
#include "../../Olympus/Hephaestus/Collision/CollisionArea.hpp"
#include "../../Olympus/Hephaestus/Scene/Scene.hpp"

class Merchant: Sprite {
    CollisionArea merchantCollision = CollisionArea({0,0,0}, {64, 64, 0}, "Merchant", std::bind(&Merchant::overlapMerchant, this, std::placeholders::_1));
    Text merchantText = { "Hello, Welcome to my Shop!", "./fonts/NewHiScore.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, topLeft, {0, 0}, pointTopLeft, 18};

    Scene* scenePointer;

    void overlapMerchant(std::string spriteID);

public:
    using Sprite::Sprite;

    void setupMerchant(Scene* scene);
};


#endif //LOWDATA_MERCHANT_HPP
