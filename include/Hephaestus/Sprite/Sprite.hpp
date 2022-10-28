/*
    Sprite.hpp
    Zachary lineman
    11/3/21
    
    =================
    Sprite Header Class
    Represents a sprite that is displayed on the screen. Sprites have their own shader, position, dimensions, rotation and texture.
    These all effect how the sprite is displayed.
    =================
*/

#ifndef OLYMPUS_SPRITE_HPP
#define OLYMPUS_SPRITE_HPP
#include <Hephaestus/Shader/Shader.hpp>
#include <Hephaestus/libs//stb_image.hpp>
#include <Hephaestus/Camera/Camera.hpp>

// GLM Math
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <string>
#include "Hephaestus/HephaestusUtility.hpp"

class Sprite {
public:
    enum Shape {
        sphere,
        square
    };

    Sprite(std::string id, std::string texturePath, SamplingType samplingType, glm::vec3 position = {300.0f, 300.0f, 0.0f}, glm::vec2 dimensions = {50.0f, 50.0f}, glm::vec3 rotation = {0.0f, 0.0f, 0.0f});
    Sprite();
    ~Sprite();

    std::string id;

    bool immovable = false;

    /*
     * Sprite Position
     */
    glm::vec3 position { };

    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);

    /// Get & Set the current X coordinate
    float getX();
    void setX(GLfloat x);

    /// Get & Set the current Y coordinate
    float getY();
    void setY(GLfloat y);

    /// Get & Set the current Z coordinate
    float getZ();
    void setZ(GLfloat z);

    /*
     * Sprite Rotation
     */
    glm::vec3 rotation { };

    glm::vec3 getRotation();
    void setRotation(glm::vec3 rotation);

    // Get & Set the current roll / X coordinate
    float getRoll();
    void setRoll(GLfloat roll);

    /// Get & Set the current pitch / Y coordinate
    float getPitch();
    void setPitch(GLfloat pitch);

    /// Get & Set the current yaw / Z coordinate
    float getYaw();
    void setYaw(GLfloat z);

    /*
     * Sprite Size
     */
    glm::vec2 dimensions { };

    glm::vec2 getDimensions();
    void setSize(glm::vec2 dimension);

    /// Get & Set the width / X coordinate
    float getWidth();
    void setWidth(GLfloat width);

    /// Get & Set the height / Y coordinate
    float getHeight();
    void setHeight(GLfloat height);

    /// Get the sprite radius
    float getRadius();

    /*
     * Sprite Tint Color
     */
    glm::vec4 tintColor { 1.0, 1.0, 1.0, 1.0};

    /*
     * Register Sprite
     */
    void registerSprite();
    bool getRegistered();

    /*
     * PhysicsCollision
     */
    virtual bool physicscCollidable();
    void setPhysicscCollidable(bool _collidable);
    bool isPhysicscCollidable = false;

    // Shape
    void setShape(Shape shape);
    virtual Shape getShape();
    Shape spriteShape = square;

    /*
     * Normal Collisions
     */
    virtual bool collidable();
    void setCollidable(bool _collidable);
    bool isCollidable = false;

    /*
     * Drawing Functions
     */
    void draw();

    virtual void move(double deltaTime);

    void setTexture(const std::string& texturePath);
    SamplingType samplingType = linear;

    void updateScreenDimensions(int width, int height);

    void updateCamera(Camera* newCamera);

    Shader shader;

    bool hidden = false;

    virtual bool canMovePhysically();

protected:
    glm::mat4 projection { };
    glm::vec2 screenSize { };

    Camera* camera;

    void createTexture(const std::string& texturePath, SamplingType samplingType);
    void createVirtualBufferObject();

    GLuint VBO, VAO, EBO, textureAtlas;

    bool registered;
};

#endif //OLYMPUS_SPRITE_HPP
