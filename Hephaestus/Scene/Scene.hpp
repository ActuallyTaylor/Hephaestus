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

#include "../Sprite/Sprite.hpp"
#include "../Text/TextManager.hpp"
#include "../UI/UIElement.hpp"
#include "../Controls/Keybind/Keybind.hpp"
#include "../Controls/ControlManager.hpp"
#include "../Collision/PhysicsCollision.hpp"
#include "../Collision/CollisionArea.hpp"
#include "../Function.hpp"

class Scene {
    /// An array of all of the sprites that managed by the window.
    vector<Sprite*> sprites;

    void drawSprites();

    vector<CollisionArea*> collisionAreas;
    PhysicsCollision checkCollision(Sprite *one, Sprite *two);
    PhysicsCollision checkAABBSphereCollision(Sprite* aabb, Sprite* sphere);

    void checkCollisionAreas();
    void applyGravity();
    void solveCollisions();
    void updateSpritePositions();

    bool physicsEnabled = false;
    bool collisionsEnabled = true;

    TextManager textManager;

    vector<UIElement*> uiElements;
    void drawUI();
    void checkUIClicks();
    void pollKeybinds();

    vector<Camera*> cameras;
    Camera* currentCamera{};
    bool shouldDrawSprite(Sprite* sprite);

    ControlManager controlManager;

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
    Shader defaultUIShader = Shader("Scene UI Shader", defaultVertexShader, defaultFragmentShader);

    GLFWwindow* parentWindow;
public:
    Scene();
    double deltaTime{};
    int width { 720 };
    int height { 720 };

    void addSprite(Sprite* sprite);
    void removeSprite(Sprite* sprite);
    Sprite* getSprite(std::string id);

    int physicsSubSteps = 2;
    void addCollisionArea(CollisionArea* collisionArea);
    void removeCollision(CollisionArea* collisionArea);
    void setPhysicsEnabled(bool _collision);
    void setCollisionsEnabled(bool _collision);

    int getNumberOfSprites();

    void addText(Text *text);
    void loadFont(std::string fontPath, int pixelHeight = 24);

    void addUIElement(UIElement *element);

    void addCamera(Camera *camera, bool setDefault);

    void addKeybind(int inKeyCode, int inAction, Function inExecutionFunction, bool executesOnHold = true);
    void addDrag(int keyCode, Function executionFunction);
    glm::vec2 getMousePosition();

    void drawScene();
    void updateScene();

    void updateSceneDimensions(int _width, int _height);
    /*
     * Set Scene Callback Functions
     *  - You do not need to set all of these. They are just there if you need them.
    */
    Function init{}, destroy{}, tick{}, update{}, render{}, screenSizeChanged{};

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

    /// Sets the render callback function
    /// \param function1 The void function pointer that will be called when render is called.
    void setScreenSizeChanged(Function function1);

    void setupScene(GLFWwindow *parent);

    /// GLFW key callback. Used to call user-defined keybindings.
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// GLFW Mouse button callback
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

#endif //OLYMPUS_SCENE_HPP
