//
//  Hephaestus.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/8/21.
//

#ifndef Hephaestus_hpp
#define Hephaestus_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>

// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Include Classes
#include "./Classes/Window/Window.hpp"
#include "./Classes/Shader/Shader.hpp"
#include "./Classes/Geometry Manager/GeometryManager.hpp"
#include "./Classes/Geometry Manager/Vertex/Vertex.hpp"
#include "./Classes/Window/WindowDelegate/WindowDelegate.hpp"

#include "./Classes/Controls/Keybind/Keybind.hpp"
#include "./Classes/Controls/Controls.hpp"

class Hephaestus {
public:
    /*
     Initializers
     */
    Hephaestus();
    void startWindowLoop();

    /*
     Object Managers
     */
    Window mainWindow;
    WindowDelegate windowDelegate;

    /*
     API Functions
     */
    void addKeybind(Keybind keybind);

    //Create Sprites
    void addSprite(string id, string texturePath);
    void addSprite(string id, string texturePath, vec3 position, vec2 size, vec3 rotation);

    //Manage Sprites
    void moveSprite(string id, vec3 position);
    void rotateSprite(string id, vec3 rotation);
    void scaleSprite(string id, vec2 size);

    Sprite& getSprite(string id);

    /*
     OpenGL Callback Functions
     */
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowCallback(GLFWwindow* window, int width, int height);
private:
    /*
     Object Managers
     */
    GeometryManager geometryManager = GeometryManager();
    Controls controls = Controls();
};

#endif /* Hephaestus_hpp */
