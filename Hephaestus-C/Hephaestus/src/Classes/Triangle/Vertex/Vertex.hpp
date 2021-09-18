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
#include "Vector3.hpp"
#include "Vector2.hpp"

struct Vertex {
    Vertex(Vector3 coordinate, Vector3 color, Vector2 texture);
    Vector3 coordinate, color;
    Vector2 texture;
    
    bool operator == (Vertex& rhs);
    bool operator != (Vertex& rhs);
    
    bool operator == (const Vertex& rhs);
    bool operator != (const Vertex& rhs);

};

#endif /* Vertex_hpp */
