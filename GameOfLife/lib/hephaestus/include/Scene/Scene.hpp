/*
    Scene.hpp
    Zachary lineman
    1/3/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_SCENE_HPP
#define OLYMPUS_SCENE_HPP

#include <string>
#include <vector>

#include "../Window/Sprite/Sprite.hpp"
#include "../Window/Text/TextManager.hpp"
#include "../Window/UI/UIElement.hpp"
#include "../Window/Controls/Keybind/Keybind.hpp"
#include "../Window/Controls/ControlManager.hpp"
#include "../Window/Collision/Collision.hpp"

class Scene {
    /// An array of all of the sprites that managed by the window.
    vector<Sprite*> sprites;
    void drawSprites();
    void moveSprites();
    Collision checkCollision(Sprite *one, Sprite *two);
    Collision checkAABBSphereCollision(Sprite* aabb, Sprite* sphere);
    void checkCollisions();
    bool shouldCheckCollisions = true;

    TextManager textManager;

    vector<UIElement*> uiElements;
    void drawUI();
    void checkUIClicks();
    glm::vec2 getMousePosition();
    void pollDragging();

    vector<Camera*> cameras;
    Camera* currentCamera{};

    ControlManager controlManager;

    int width { 720 };
    int height { 720 };

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
    Shader defaultSpriteShader = Shader("Scene Sprite Shader", defaultVertexShader, defaultFragmentShader);
    Shader defaultUIShader = Shader("Scene UIr Shader", defaultVertexShader, defaultFragmentShader);

    GLFWwindow* parentWindow;

public:
    Scene();
    double deltaTime{};

    void addSprite(Sprite *sprite);
    void setShouldCheckCollision(bool _collision);

    void addText(Text *text);
    void loadFont(std::string fontPath);

    void addUIElement(UIElement *element);

    void addCamera(Camera *camera, bool setDefault);

    void addKeybind(int inKeyCode, int inAction, Function inExecutionFunction);
    void addDrag(int keyCode, Function executionFunction);

    void drawScene();
    void updateScene();
    /*
     * Set Scene Callback Functions
     *  - You do not need to set all of these. They are just there if you need them.
    */
    Function init{}, destroy{}, tick{}, update{}, render{};

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

    void setupScene(GLFWwindow *parent);

    /// GLFW key callback. Used to call user-defined keybindings.
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// GLFW Mouse button callback
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

#endif //OLYMPUS_SCENE_HPP
