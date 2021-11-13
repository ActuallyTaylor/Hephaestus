/*
    Window.hpp
    Zachary lineman
    11/1/21

    =================
    Window Header Class
    Holds all the functions that interact directly with open gl.
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
#include "./Sprite/Sprite.hpp"
#include "./Controls/ControlManager.hpp"
#include "./Camera/Camera.hpp"

class Window {
private:
    /// The name of the window.
    std::string windowName;
    /// The pixel width of the window.
    int width { 720 };
    /// The pixel height of the window.
    int height { 720 };

    bool printFrames { true };

    /// The GLFW window that this class wraps.
    GLFWwindow *window;
    /// The control manager of the window.
    ControlManager controlManager = ControlManager();

    /// The current camera
    Camera* currentCamera;

    /*
     * Runtime Functions
     */
    /// Calls the user-defined init callback.
    void _init ();
    /// Calls the user-defined destroy callback along with doing behind the scenes cleanup.
    void _destroy ();
    /// Calls the user-defined tick callback.
    void _tick ();
    /// Calls the user-defined update callback.
    void _update ();
    /// Calls the user-defined render callback.
    void _render ();

    /*
     * Static GLFW callbacks
     */
    /// GLFW key callback. Used to call user-defined keybindings.
    /// \param window
    /// \param key
    /// \param scancode
    /// \param action
    /// \param mods
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// GLFW Window resize callback. Used to update the internal window size tracking.
    static void windowCallback(GLFWwindow* window, int width, int height);

    /*
     * Static Camera Callbacks
     */
    /// Gets called when the cameras position changes
    static void cameraPositionChanged();
    /// Gets called when the cameras rotation changes
    static void cameraRotationChanged();
    /// Gets called when the cameras target changes
    static void cameraTargetChanged();
public:
    /*
     * Initializers
     */
    /// **DO NOT USE** Default initialization of the window.
    Window();
    /// The correct window initializer.
    /// \param windowName The name of the window
    /// \param width Integer that represents the starting height of the window
    /// \param height Integer that represents the starting width of the window
    Window(std::string windowName, int width, int height);

    /*
     * Class functions
     */
    /// Calling this function displays the window and starts the window loop.
    /// The window loop drawing sprites & calling user-defined callbacks
    void windowLoop();

    /// Adds a sprite into the window
    /// \param sprite The sprite that should be added into the window. The given sprite is copied into the sprites vector.
    /// \return A pointer to the spite located in the sprites vector.
    Sprite* addSprite(Sprite sprite);

    /// Adds a keybind to the window's control manager
    /// \param keybind The keybind that should be added to the control manager.
    void addKeybind(Keybind keybind);

    /// Adds a keybind to the window's control manager
    /// \param keybind The keybind that should be added to the control manager.
    Camera* addCamera(Camera camera);

    /*
     * Variables
     */
    /// A set of function variables that are set when the user sets a user-defined callback.
    Function init, destroy, tick, update, render;

    /// An array of all of the sprites that managed by the window.
    vector<Sprite> sprites;

    vector<Camera> cameras;
};

#endif //OLYMPUS_WINDOW_HPP
