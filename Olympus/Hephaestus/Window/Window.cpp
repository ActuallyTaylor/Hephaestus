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

Window::Window() {
    textManager = TextManager();

}

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
//    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    textManager = TextManager();
    textManager.setup();
}

void Window::windowLoop() {
    _init();
    // Disabled to allow
//    glEnable(GL_DEPTH_TEST);

    double currentTime = glfwGetTime();
    double lastTime = glfwGetTime();
    double lastFrameCountTime = glfwGetTime();

    int framesThisSecond = 0;
    self = this;
    // Uncomment this to delimit framerate. Currently, limited because physics breaks.
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(0);

    Text renderingText = Text("", "./fonts/SFNSRounded.ttf", glm::vec2(10, 645), glm::vec4(1.0,1.0,1.0,1.0));
    textManager.addText(&renderingText);

    while (!glfwWindowShouldClose(window)) {
        framesThisSecond ++;

        if(currentTime - lastFrameCountTime >= 1.0) {
            if (printFrames) {
                printf("======\n");
                printf("%f ms/frame\n", 1000.0 / double(framesThisSecond));
                printf("%d frames per second\n", framesThisSecond);
            }
            framesPerSecond = framesThisSecond;
            framesThisSecond = 0;
            lastFrameCountTime += 1.0;
        }

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Call user-defined callback functions
        const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        _tick();
        _update();
        _render();
        const std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        renderingText.text = "Frame Calculations " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + "µs ≈ " + std::to_string((end - start) / 1ms) + "ms ≈ " + std::to_string((end - start) / 1s) + "s.";

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

    for(Sprite *sprite : sprites) {
        sprite->draw();
    }

    textManager.draw();

    for (UIElement *element: uielements) {
        printf("Drawing Element");
        element->draw();
    }

    if (render != nullptr) {
        render();
    }
    glDisable(GL_BLEND);
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
    glViewport(0, 0, width, height);
//    glOrtho(0.0f, width, height, 0.0f, -1000.0f, 1000.0f );

    for (Sprite *sprite: self->sprites) {
        sprite->updateScreenDimensions(width, height);
    }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    self->controlManager.executeKeybinds(button, action);
}

void Window::addSprite(Sprite *sprite) {
    sprite->updateScreenDimensions(width, height);
    sprite->updateCamera(currentCamera);
    sprite->registerSprite();
    sprites.push_back(sprite);
}

void Window::addKeybind(Keybind keybind) {
    controlManager.addKeybind(keybind);
}

void Window::addText(Text* text) {
    textManager.addText(text);
}

void Window::addUIElement(UIElement* element) {
    uielements.push_back(element);
}

void Window::loadFont(std::string fontPath) {
    textManager.loadFont(fontPath);
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

float clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}

void Window::checkCollisions() {
    for (int x = 0; x < sprites.size(); ++x) {
        for (int y = x+1; y < sprites.size(); ++y) {
            Sprite* sprite = sprites[x];
            Sprite* checkSprite = sprites[y];

            Collision collision { checkCollision(sprite, checkSprite) };
            if(collision.successful) {
                collision.perform(deltaTime);
            }
        }
    }
}

// https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
Collision Window::checkCollision(Sprite *one, Sprite *two) {
    if (one != two) {
        if (one->getShape() == Sprite::sphere && two->getShape() == Sprite::sphere) {
            // Calculate collision for sphere & sphere
            float combinedRadius = one->getRadius() + two->getRadius();
            glm::vec3 delta = {two->getX() - one->getX(), two->getY() - one->getY(), 0.0};
            float deltaLength = glm::length(delta);
            if (deltaLength <= combinedRadius) {
                float penetration = (combinedRadius - deltaLength);

                return {true, one, two, delta, glm::vec3(penetration, 0.0, 0.0)};
            }
        } else if (one->getShape() == Sprite::sphere && two->getShape() == Sprite::square) {
            // Sphere - AABB collision
            return checkAABBSphereCollision(two, one);
        } else if (one->getShape() == Sprite::square && two->getShape() == Sprite::sphere) {
            // AABB - Sphere collision
            return checkAABBSphereCollision(one, two);
        } else if (one->getShape() == Sprite::square && two->getShape() == Sprite::square) {
            // AABB collision
            if ((one->getX() <= two->getX() + two->getWidth() && one->getX() + one->getWidth() >= two->getX()) &&
                (one->getY() <= two->getY() + two->getHeight() && one->getY() + one->getHeight() >= two->getY()) &&
                (one->getZ() <= two->getZ() && one->getZ() + 0 >= two->getZ())) {
                glm::vec3 delta = one->getPosition() - two->getPosition();
                return {true, one, two, delta, glm::vec3(1.0f)};
            }
        }
        return {false, nullptr, nullptr, glm::vec3(1.0f), glm::vec3(1.0f)};
    }
    return {false, nullptr, nullptr, glm::vec3(1.0f), glm::vec3(1.0f)};
}

// https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
Collision Window::checkAABBSphereCollision(Sprite* aabb, Sprite* sphere) {
    glm::vec2 center {sphere->getPosition() + sphere->getRadius()};
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents {aabb->getWidth() / 2.0f, aabb->getHeight() / 2.0f};
    glm::vec2 aabb_center(
            aabb->getX() + aabb_half_extents.x,
            aabb->getY() + aabb_half_extents.y
//            aabb->getZ() + aabb_half_extents.z
    );
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;

    return Collision(glm::length(difference) < sphere->getRadius(), aabb, sphere, {difference, 0.0}, {difference, 0.0});
}

glm::vec2 Window::getMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { xpos, ypos };
}