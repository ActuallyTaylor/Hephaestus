/*
    Hephaestus.hpp
    Zachary lineman
    11/3/21

    =================
    Hephaestus header class.
    The Hephaestus class holds the interface used to interact with the engine. You can create sprites and shaders from
    here, along with adding keybinds to register keypresses with the engine.
    =================
*/

#include <iostream>

#ifndef OLYMPUS_HEPHAESTUS_HPP
#define OLYMPUS_HEPHAESTUS_HPP

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++ Classes
#include <string>
#include <vector>

// Custom Classes
#include "Shader/Shader.hpp"
#include "Scene/Scene.hpp"

class Hephaestus {
private:
    std::string name;

    /// The GLFW window that this class wraps.
    GLFWwindow *window;
    /// The pixel width of the window.
    int width { 480 };
    /// The pixel height of the window.
    int height { 270 };

    bool printFrames { false };

    Scene* currentScene;

    double deltaTime{};
    int framesPerSecond { };

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
public:
    /// Initializer for the Hephaestus class
    /// \param name The name of the window that will be created.
    explicit Hephaestus(const std::string& name);
    explicit Hephaestus(std::string name, int width, int height);

    /// Called to start the window loop. This will display the window onto screen.
    void startWindowLoop();

    void openScene(Scene* scene);

    /// Creates a shader that can be used when creating a sprite
    /// \param vertexPath The string path to the vertex shader
    /// \param fragmentPath The string path to the fragment shader
    /// \return A new setup shader with the speicifed vertex and fragment shader
    static Shader createShader(std::string identifier, std::string vertexPath, std::string fragmentPath);

    /// Returns the current active window frames per second.
    [[nodiscard]] int getFPS() const;

    [[nodiscard]] int windowWidth() const;
    [[nodiscard]] int windowHeight() const;
};

#endif //OLYMPUS_HEPHAESTUS_HPP
