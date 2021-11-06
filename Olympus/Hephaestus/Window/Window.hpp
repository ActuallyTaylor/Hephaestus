/*
    Window.hpp
    Zachary lineman
    11/1/21

    =================
    DESCRIPTION
    =================
*/

// Parent
#include "../Hephaestus.hpp"

#ifndef OLYMPUS_WINDOW_HPP
#define OLYMPUS_WINDOW_HPP
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++ Classes
#include <string>
#include <vector>

// Custom Classes
#include "../Sprite/Sprite.hpp"
#include "./Controls/ControlManager.hpp"

typedef void (*Function)();

class Window {
private:
    std::string windowName;
    int width { 720 };
    int height { 720 };

    GLFWwindow *window;
    ControlManager controlManager = ControlManager();

    /*
     * Runtime Functions
     */
    void _init ();
    void _destroy ();
    void _tick ();
    void _update ();
    void _render ();

    /*
     * Static GLFW callbacks
     */
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowCallback(GLFWwindow* window, int width, int height);
public:
    Window();
    Window(std::string windowName, int width, int height);

    void windowLoop();

    Sprite* addSprite(Sprite sprite);
    void addKeybind(Keybind keybind);

    Function init, destroy, tick, update, render;

    vector<Sprite> sprites;

};

#endif //OLYMPUS_WINDOW_HPP
