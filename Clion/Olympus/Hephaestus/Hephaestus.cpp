//
// Created by Zachary lineman on 11/1/21.
//

#include "Hephaestus.hpp"

Hephaestus::Hephaestus(const std::string& name) {
    this->name = name;
    std::cout << name << std::endl;
}

Window Hephaestus::createWindow(const std::string& windowName, int width, int height) {
    Window window = Window(windowName, width, height);
    return window;
//    windows.push_back(window);
}
