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

    /// Creates a shader that can be used when creating a sprite
    /// \param vertexPath The string path to the vertex shader
    /// \param fragmentPath The string path to the fragment shader
    /// \return A new setup shader with the speicifed vertex and fragment shader
    static Shader createShader(std::string vertexPath, std::string fragmentPath);

    /// Creates a camera object
    /// \return A reference to the created camera
    Camera* createCamera();

    /*
     * Create Dynamic Data
     *  - Used to create objects and data that you use in your games
     */
    /// Adds a sprite onto the screen
    /// \param shader The shader that should be used to render the sprite
    /// \param texturePath The path to the texture that the sprite should dispaly
    /// \param position The vector3 coordinates of the sprite (x, y, z). X: Left -> Right, Y: Top -> Bottom, Z: Into Screen -> Out of Screen
    /// \param size A vector2 that describes the size of the sprite (x, y). X: Width, Y: Height.
    /// \param rotation A vector3 that describes the rotation of the sprite (x, y, z). X: Roll, Y: Pitch, Z: Yaw
    /// \return
    Sprite* addSprite(Shader shader, std::string texturePath,
                      glm::vec3 position = glm::vec3(300.0f, 300.0f, 0.0f),
                      glm::vec2 size = glm::vec2(50.0f, 50.0f),
                      glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));

    /// Registers a keybind to the engine. Any keybind registered here will be checked whenever a key press is detected.
    /// \param keyCode The GLFW key code for the key. Ex: GLFW_KEY_UP
    /// \param action The GLFW action code. Ex: GLFW_REPEAT
    /// \param executionFunction A pointer to the void function that will be executed when the key is pressed.
    void addKeybind(int keyCode, int action, Function executionFunction);

    /*
     * Set Hephaestus Callback Functions
     *  - You do not need to set all of these. They are just there if you need them.
    */
    /// Sets the initialization callback function
    /// \param function1 The void function pointer that will be called when init is called.
    void setInit(Function function1);

    /// Sets the destroy callback function
    /// \param function1 The void function pointer that will be called when destroy is called.
    void setDestroy(Function function1);

    /// Sets the tick callback function
    /// \param function1 The void function pointer that will be called when tick is called.
    void setTick(Function function1);

    /// Sets the update callback function
    /// \param function1 The void function pointer that will be called when update is called.
    void setUpdate(Function function1);

    /// Sets the render callback function
    /// \param function1 The void function pointer that will be called when render is called.
    void setRender(Function function1);

};

#endif //OLYMPUS_HEPHAESTUS_HPP
