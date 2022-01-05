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
#include <glm/gtx/string_cast.hpp>

// C++ Classes
#include <string>
#include <vector>

// Custom Classes
class Scene;

class Window {
private:
    /// The name of the window.
    std::string windowName;
    bool printFrames { false };

    double deltaTime{};

    /*
     * Runtime Functions
     */
    /// Calls the user-defined init callback.
    void _init () const;
    /// Calls the user-defined destroy callback along with doing behind the scenes cleanup.
    void _destroy () const;
    /// Calls the user-defined tick callback.
    void _tick () const;
    /// Calls the user-defined update callback.
    void _update () const;
    /// Calls the user-defined render callback.
    void _render () const;

    /*
     * Static GLFW callbacks
     */
    /// GLFW Window resize callback. Used to update the internal window dimensions tracking.
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

    /// The GLFW window that this class wraps.
    GLFWwindow *window;

    /*
     * Class functions
     */
    /// Calling this function displays the window and starts the window loop.
    /// The window loop drawing sprites & calling user-defined callbacks
    void windowLoop();

    //// Get the current mouse position
    glm::vec2 getMousePosition() const;

    int framesPerSecond { };

    void openScene(Scene* scene);
    Scene* currentScene;

    /// The pixel width of the window.
    int width { 720 };
    /// The pixel height of the window.
    int height { 720 };
};

#endif //OLYMPUS_WINDOW_HPP
