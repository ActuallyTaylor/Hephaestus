#include <iostream>
#include <vector>
#include "../../Hephaestus/Hephaestus.hpp"

#include "mainLevelScene.hpp"

Hephaestus engine = Hephaestus("Conways Game of Life", 480, 320);

int main() {
    MainLevelScene mainLevel = MainLevelScene(&engine);
    engine.openScene(&mainLevel.scene);
    engine.startWindowLoop();

    return 0;
}