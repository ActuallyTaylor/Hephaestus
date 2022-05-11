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
#include "../../../Hephaestus/Sprite/Sprite.hpp"
#include "../../../Hephaestus/Collision/CollisionArea.hpp"
#include "../../../Hephaestus/Scene/Scene.hpp"

class Merchant: Sprite {
    CollisionArea merchantCollision = CollisionArea({0,0,0}, {64, 64, 0}, "Merchant", std::bind(&Merchant::overlapMerchant, this, std::placeholders::_1), std::bind(&Merchant::leaveMerchant, this, std::placeholders::_1));
    Text merchantText = { "Hello, Welcome to my Shop!", "./fonts/NewHiScore.ttf", { 1.0f, 1.0f, 1.0f, 1.0f }, bottomCenter, {0, 50}, pointBottomCenter, 26};

    Scene* scenePointer;

    void overlapMerchant(std::string spriteID);
    void leaveMerchant(std::string spriteID);

public:
    using Sprite::Sprite;

    void setupMerchant(Scene* scene);
};


#endif //LOWDATA_MERCHANT_HPP
