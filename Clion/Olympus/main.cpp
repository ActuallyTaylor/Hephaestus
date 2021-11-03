#include <iostream>
#include "Hephaestus/Hephaestus.hpp"

int main() {
    Hephaestus engine = Hephaestus("Olympus Hephaestus Client");
    Window mainWindow = engine.createWindow("Hephaestus Engine", 720, 720);
    mainWindow.windowLoop();

    return 0;
}
