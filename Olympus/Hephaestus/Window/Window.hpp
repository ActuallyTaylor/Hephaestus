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
#include "./Sprite/Sprite.hpp"
#include "./Sprite/PhysicsSprite/PhysicsSprite.hpp"
#include "./Controls/ControlManager.hpp"
#include "./Camera/Camera.hpp"
#include "./Text/TextManager.hpp"
#include "./UI/UIElement.hpp"

class Window {
private:
    /// The name of the window.
    std::string windowName;
    bool printFrames { false };

    double deltaTime{};

    /// The GLFW window that this class wraps.
    GLFWwindow *window;
    /// The control textManager of the window.
    ControlManager controlManager = ControlManager();

    /// Manages all text displayed on the screen
    TextManager textManager { };

    /// The current camera
    Camera* currentCamera{};

   const char *defaultVertexShader = R""""(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texturePosition;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoord = texturePosition;
}
)"""";

    const char *defaultFragmentShader = R""""(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
)"""";
    Shader defaultSpriteShader = Shader(defaultVertexShader, defaultFragmentShader);
    Shader defaultUIShader = Shader(defaultVertexShader, defaultFragmentShader);

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

    /// GLFW Window resize callback. Used to update the internal window dimensions tracking.
    static void windowCallback(GLFWwindow* window, int width, int height);

    /// GLFW Mouse button callback
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    /*
     * Static Camera Callbacks
     */
    /// Gets called when the cameras position changes
    static void cameraPositionChanged();
    /// Gets called when the cameras rotation changes
    static void cameraRotationChanged();
    /// Gets called when the cameras target changes
    static void cameraTargetChanged();

    /*
     * Class Functions
     */
    Collision checkCollision(Sprite *one, Sprite *two);
    Collision checkAABBSphereCollision(Sprite* aabb, Sprite* sphere);

    void checkUIClicks();
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
    void addSprite(Sprite *sprite);

    /// Adds a keybind to the window's control textManager
    /// \param keybind The keybind that should be added to the control textManager.
    void addKeybind(Keybind keybind);
    void addDrag(Keybind keybind);
    
    /// Adds a keybind to the window's control textManager
    /// \param keybind The keybind that should be added to the control textManager.
    void addCamera(Camera *camera);

    void addText(Text* text);

    void loadFont(std::string fontPath);

    void addUIElement(UIElement *element);

    //// Get the current mouse position
    glm::vec2 getMousePosition();

    /*
     * Collision Checking
     */
    void checkCollisions();
    bool shouldCheckCollisions = true;

    /*
     * Variables
     */
    /// A set of function variables that are set when the user sets a user-defined callback.
    Function init{}, destroy{}, tick{}, update{}, render{};

    /// An array of all of the sprites that managed by the window.
    vector<Sprite*> sprites;

    vector<Camera*> cameras;

    vector<UIElement*> uiElements;

    int framesPerSecond { };

    /// The pixel width of the window.
    int width { 720 };
    /// The pixel height of the window.
    int height { 720 };
};

#endif //OLYMPUS_WINDOW_HPP
