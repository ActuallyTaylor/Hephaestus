//
//  Sprite.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/20/21.
//

#ifndef GeometryBuffer_hpp
#define GeometryBuffer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "CompressedData.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

class Sprite {
    /*
     Construction
     */
public:
    Sprite(string id, vector<Vertex> vertices, Shader shader, string texturePath);
    Sprite(string id, Shader shader, string texturePath);

    string id;
    vec2 screenDimensions = vec2(0.0, 0.0);

    /*
     State Variables
     */
    vec3 position = vec3(400.0f, 400.0f, 0.0f);
    vec2 size = vec2(300.0f, 300.0f);
    //                    x  ,  y  ,  z
    vec3 rotation = vec3(0.0f, 0.0f, 0.0f);

    /*
     Functions
     */
    void draw();
    
    vec3 getPosition();
    vec2 getSize();
    vec3 getRotation();

    
    void updatePosition(vec3 newPosition);
    void updateSize(vec2 newSize);
    void updateRotation(vec3 newRotation);
    
    CompressedData compressTriangleVertices();
    

private:
    /*
     Variables
     */
    Shader shader;
    GLuint VBO, VAO, EBO, textureAtlas;
    GLint indiceCount;
    
    /*
     Arrays
     */
    vector<Vertex> vertices;
    
    /*
     Functions
     */
    void createVirtualBufferObject();
    void createTexture(string texturePath);
};

#endif /* GeometryBuffer_hpp */
