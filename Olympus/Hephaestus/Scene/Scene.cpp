/*
    Scene.cpp
    Zachary lineman
    1/3/22
    
    =================
    DESCRIPTION
    =================
*/

#include "Scene.hpp"

Scene* self_scene;

Scene::Scene() {
    controlManager = ControlManager();
    textManager = TextManager();
    textManager.setup();
    self_scene = this;

    defaultSpriteShader.setup();
    defaultUIShader.setup();
}

void Scene::setupScene(GLFWwindow *parent) {
    parentWindow = parent;
    self_scene = this;
    glfwSetKeyCallback(parent, keyCallback);
    glfwSetMouseButtonCallback(parent, mouseButtonCallback);
}

void Scene::drawSprites() {
    for(Sprite *sprite : sprites) {
        if(shouldDrawSprite(sprite)) {
            sprite->draw();
        }
    }
}

bool Scene::shouldDrawSprite(Sprite* sprite) {
    if ((sprite->getX() <= -currentCamera->position.x + width && sprite->getX() + sprite->getWidth() >= -currentCamera->position.x) &&
        (sprite->getY() <= -currentCamera->position.y + height && sprite->getY() + sprite->getHeight() >= -currentCamera->position.y)) {
        return true;
    }
    return false;
}

void Scene::drawUI() {
    textManager.draw();
    for(UIElement *element: uiElements) {
        element->draw();
    }
}

void Scene::addSprite(Sprite *sprite) {
    sprite->updateScreenDimensions(width, height);

    sprite->updateCamera(currentCamera);

    sprite->registerSprite();
    sprite->shader = defaultSpriteShader;
    sprites.push_back(sprite);
}

void Scene::addText(Text *text) {
    textManager.addText(text);
}

void Scene::loadFont(std::string fontPath, int pixelHeight) {
    textManager.loadFont(fontPath, pixelHeight);
}

void Scene::addUIElement(UIElement *element) {
    element->addShader(defaultUIShader);
    uiElements.push_back(element);
}

glm::vec2 Scene::getMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(parentWindow, &xpos, &ypos);
    return { xpos, height - ypos };
}

void Scene::addCamera(Camera *camera, bool setDefault) {
    camera->setUpdatePositionCallback(cameraPositionChanged);
    camera->setUpdateRotationCallback(cameraRotationChanged);
    camera->setUpdateRotationCallback(cameraTargetChanged);
    cameras.push_back(camera);

    if(setDefault) {
        currentCamera = camera;
        for (Sprite *sprite: sprites) {
            sprite->updateCamera(currentCamera);
        }
    }
}

void Scene::setInit(Function function1) {
    init = function1;
}

void Scene::setDestroy(Function function1) {
    destroy = function1;
}

void Scene::setTick(Function function1) {
    tick = function1;
}

void Scene::setUpdate(Function function1) {
    update = function1;
}

void Scene::setRender(Function function1) {
    render = function1;
}

void Scene::addKeybind(int inKeyCode, int inAction, Function inExecutionFunction) {
    Keybind keybind = Keybind{inKeyCode, inAction, inExecutionFunction};
    controlManager.addKeybind(keybind);
}

void Scene::addDrag(int keyCode, Function executionFunction) {
    Keybind keybind = Keybind{keyCode, GLFW_PRESS, executionFunction};
    controlManager.addDrag(keybind);
}

void Scene::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        self_scene->controlManager.executeKeybinds(key, action);
    }

}

void Scene::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    self_scene->controlManager.executeKeybinds(button, action);
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(GLFW_PRESS == action) {
            self_scene->checkUIClicks();
            self_scene->controlManager.leftDown = true;
        } else if(GLFW_RELEASE == action) {
            self_scene->controlManager.leftDown = false;
        }
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if(GLFW_PRESS == action) {
            self_scene->checkUIClicks();
            self_scene->controlManager.rightDown = true;
        }
        else if(GLFW_RELEASE == action) {
            self_scene->controlManager.rightDown = false;
        }
    }
}

void Scene::checkUIClicks() {
    glm::vec2 clickPosition = getMousePosition();

    for(UIElement *element: uiElements) {
        if ((element->position.x + element->dimensions.x >= clickPosition.x && element->position.x <= clickPosition.x) &&
            (element->position.y + element->dimensions.y >= clickPosition.y && element->position.y <= clickPosition.y)) {
            element->isClicked = true;
            element->primaryFunction();
        } else {
            element->isClicked = false;
        }
    }
}

float clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}

void Scene::checkCollisions() {
    if(shouldCheckCollisions) {
        for (int x = 0; x < sprites.size(); ++x) {
            Sprite *sprite = sprites[x];

            if(sprite->collidable()) {
                for (int y = x+1; y < sprites.size(); ++y) {
                    Sprite *checkSprite = sprites[y];
                    if (checkSprite->collidable()) {
                        Collision collision { checkCollision(sprite, checkSprite) };
                        if(collision.successful) {
                            collision.perform(deltaTime);
                        }
                    }
                }
            }
        }
    }
}

// https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
Collision Scene::checkCollision(Sprite *one, Sprite *two) {
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
Collision Scene::checkAABBSphereCollision(Sprite* aabb, Sprite* sphere) {
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

void Scene::setShouldCheckCollision(bool _collision) {
    shouldCheckCollisions = _collision;
}

void Scene::drawScene() {
    drawUI();
    drawSprites();
}

void Scene::moveSprites() {
    for (Sprite* sprite: sprites) {
         if(sprite->canMove()) {
             sprite->move(deltaTime);
         }
    }
}

void Scene::updateScene() {
    moveSprites();
    checkCollisions();
    pollKeybinds();
}

void Scene::pollKeybinds() {
    this->controlManager.executeHolding();
    this->controlManager.executeDragging();
}

void Scene::updateSceneDimensions(int _width, int _height) {
    width = _width;
    height = _height;

    for (Sprite *sprite: sprites) {
        sprite->updateScreenDimensions(width, height);
    }
    textManager.updateScreenDimensions(width, height);

    for (UIElement *element: uiElements) {
        element->updateScreenDimensions(width, height);
    }
}

int Scene::getNumberOfSprites() {
    return sprites.size();
}

void Scene::cameraPositionChanged() {

}

void Scene::cameraRotationChanged() {

}

void Scene::cameraTargetChanged() {

}