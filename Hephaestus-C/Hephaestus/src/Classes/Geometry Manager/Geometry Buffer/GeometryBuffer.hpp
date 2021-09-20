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

#include "Triangle.hpp"
#include "Cube.hpp"
#include "Vector3.hpp"
#include "CompressedData.hpp"
#include "Shader.hpp"

class GeometryBuffer {
    vector<Triangle> triangles = {};
    vector<Cube> cubes = {};
    
    Shader *shader;
    void createVirtualBufferObject();

    GLuint VBO, VAO, EBO, textureAtlas;

    GLint indiceCount;
    
    CompressedData compressTriangleVertices();
private:
};

#endif /* GeometryBuffer_hpp */
