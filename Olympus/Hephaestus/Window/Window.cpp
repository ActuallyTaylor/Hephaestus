/*
    Window.cpp
    Zachary lineman
    11/1/21

    =================
    Implementations for all the Window.hpp class functions
    =================
*/
#include "Window.hpp"

Window* self;

Window::Window() { }

Window::Window(std::string sentWindowName, int sentWidth, int sentHeight) {
    // Set unset class variables
    windowName = sentWindowName;
    width = sentWidth;
    height = sentHeight;

    // Initialize GLFW library
    if (!glfwInit()) {
        exit(-9);
    }

    // Set macOS specific flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    // Start GLEW extension handler
    glewInit();

    glViewport(0, 0, width, height);

    // Set GLFW key callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowCallback);
}

void Window::windowLoop() {
    _init();
    glEnable(GL_DEPTH_TEST);
    // Holds the last frame time + the current amount of frames that have in a second.
    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    int framesThisSecond = 0;

    self = this;
    while (!glfwWindowShouldClose(window)) {
        if (printFrames) {
            framesThisSecond ++;

            if(currentFrame - lastFrame >= 1.0) {
                printf("======\n");
                printf("%f ms/frame\n", 1000.0/double(framesThisSecond));
                printf("%d frames per second\n", framesThisSecond);
                framesThisSecond = 0;
//                lastFrame += 1.0;
            }
        }

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Call user-defined callback functions
        _update();
        _render();

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
}

void Window::_init() {
    if (init != nullptr) {
        init();
    }
}

void Window::_destroy() {
    if (destroy != nullptr) {
        destroy();
    }
    glfwTerminate();
}

void Window::_tick() {
    if (tick != nullptr) {
        tick();
    }
}

void Window::_update() {
    for (Sprite* sprite: sprites) {
        sprite->move(deltaTime);
    }

    checkCollisions();
    if (update != nullptr) {
        update();
    }
}

void Window::_render() {
    // Clear the screen
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Draw all sprites into the screen.
    for(Sprite *sprite : sprites) {
        sprite->draw();
    }
    glDisable(GL_BLEND);

    if (render != nullptr) {
        render();
    }
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    printf("KeyCode: %d, ScanCode: %d, Action: %d, Mods: %d\n", key, scancode, action, mods);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        self->controlManager.executeKeybinds(key, action);
    }
}

void Window::windowCallback(GLFWwindow *window, int width, int height) {
    self->width = width;
    self->height = height;

    for (Sprite *sprite: self->sprites) {
        sprite->updateScreenDimensions(width, height);
    }
}

void Window::addSprite(Sprite *sprite) {
    sprite->updateScreenDimensions(width, height);
    sprite->updateCamera(currentCamera);
    sprites.push_back(sprite);
}

void Window::addKeybind(Keybind keybind) {
    controlManager.addKeybind(keybind);
}

void Window::cameraPositionChanged() {

}

void Window::cameraRotationChanged() {

}

void Window::cameraTargetChanged() {

}

void Window::addCamera(Camera* inCamera) {
    inCamera->setUpdatePositionCallback(cameraPositionChanged);
    inCamera->setUpdateRotationCallback(cameraRotationChanged);
    inCamera->setUpdateRotationCallback(cameraTargetChanged);
    currentCamera = inCamera;
    cameras.push_back(inCamera);

    for (Sprite *sprite: sprites) {
        sprite->updateCamera(currentCamera);
    }
}

void Window::checkCollisions() {
    for (int x = 0; x < sprites.size(); ++x) {
        for (int y = x+1; y < sprites.size(); ++y) {
            Sprite* sprite = sprites[x];
            Sprite* checkSprite = sprites[y];

            Collision result { checkCollision(sprite, checkSprite) };
            if(std::get<0>(result)) {
                PhysicsSprite* pSprite = dynamic_cast<PhysicsSprite *>(sprite);
                PhysicsSprite* cpSprite = dynamic_cast<PhysicsSprite *>(checkSprite);

                if (pSprite != nullptr && checkSprite != nullptr) {
                    pSprite->collide(cpSprite, std::get<1>(result));
                }
            }
        }
    }
}

// https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
Collision Window::checkCollision(Sprite *one, Sprite *two) {
    if (one != two) {
        if(one->getShape() == Sprite::sphere && two->getShape() == Sprite::sphere) {
            // Calculate collision for sphere & sphere
            float combinedRadius = one->getRadius() + two->getRadius();
            glm::vec3 delta = one->getPosition() - two->getPosition();
            float deltaLength = glm::length(delta);
            if (deltaLength <= combinedRadius) {
                float penetration = (combinedRadius - deltaLength);
                glm::vec3 normal = glm::normalize(delta);
//                    glm::vec3 localA = normal * one->getRadius();
//                    glm::vec3 localB = -normal * two->getRadius();

                return Collision(true, normal);
            }
        }
    }
    return Collision(false, 0);
}

PhysicsSprite::Direction Window::VectorDirection(glm::vec2 target) {
    glm::vec2 compass[] = {
            glm::vec2(0.0f, 1.0f),	// up
            glm::vec2(1.0f, 0.0f),	// right
            glm::vec2(0.0f, -1.0f),	// down
            glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (PhysicsSprite::Direction)best_match;
}