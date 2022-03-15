#include <iostream>
#include "../Olympus/Hephaestus/Hephaestus.hpp"
#include "Scenes/MenuScene.hpp"

Hephaestus engine = Hephaestus("Low Data");

int main() {
    MenuScene menuScene = MenuScene(&engine);

    engine.openScene(&menuScene.scene);
    engine.startWindowLoop();
    return 0;
}