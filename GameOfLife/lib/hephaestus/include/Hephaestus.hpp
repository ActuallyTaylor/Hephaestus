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
typedef void (*Function)();

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
#include "Window/Window.hpp"
#include "Shader/Shader.hpp"

// UI Elements
#include "Window/UI/Button/Button.hpp"

class Hephaestus {
private:
    Window window;
    std::string name;

public:
    /// Initializer for the Hephaestus class
    /// \param name The name of the window that will be created.
    explicit Hephaestus(std::string name);

    /// Called to start the window loop. This will display the window onto screen.
    void startWindowLoop();

    void openScene(Scene* scene);

    /// Creates a shader that can be used when creating a sprite
    /// \param vertexPath The string path to the vertex shader
    /// \param fragmentPath The string path to the fragment shader
    /// \return A new setup shader with the speicifed vertex and fragment shader
    static Shader createShader(std::string identifier, std::string vertexPath, std::string fragmentPath);

    //// Get the current mouse position
    glm::vec2 getMousePosition();

    void setWindowShouldCheckCollision(bool _collision);

    /// Returns the current active window frames per second.
    int getFPS() const;

    int windowWidth() const;
    int windowHeight() const;
};

#endif //OLYMPUS_HEPHAESTUS_HPP
