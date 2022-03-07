#include <iostream>
#include <vector>
#include "../Olympus/Hephaestus/Hephaestus.hpp"

#include "mainLevelScene.hpp"

Hephaestus engine = Hephaestus("Conways game of life");

int main() {
    MainLevelScene mainLevel = MainLevelScene(&engine);
    engine.openScene(&mainLevel.scene);
    engine.startWindowLoop();

    return 0;
}