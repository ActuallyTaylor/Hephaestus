//
//  Vertex.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Vertex {
    Vertex(glm::vec3 coordinate, /*glm::vec3 color,*/ glm::vec2 texture);
    glm::vec3 coordinate;//, color;
    glm::vec2 texture;
    
    bool operator == (Vertex& rhs);
    bool operator != (Vertex& rhs);
    
    bool operator == (const Vertex& rhs);
    bool operator != (const Vertex& rhs);

};

#endif /* Vertex_hpp */
