//
//  GeometryBuffer.hpp
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
#include "glm.hpp"

#include "CompressedData.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

class GeometryBuffer {
    /*
     Construction
     */
public:
    GeometryBuffer(string id, vector<Vertex> vertices, Shader shader, string texturePath);
    
    /*
     Arrays
     */
    vector<Vertex> vertices;

    /*
     Variables
     */
    Shader shader;
    GLuint VBO, VAO, EBO, textureAtlas;
    GLint indiceCount;
    string id;
    
    /*
     Functions
     */
    void createVirtualBufferObject();
    void draw();
    
    CompressedData compressTriangleVertices();
};

#endif /* GeometryBuffer_hpp */
