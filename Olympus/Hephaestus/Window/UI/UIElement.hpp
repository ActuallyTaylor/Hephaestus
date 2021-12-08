/*
    UIElement.hpp
    Zachary lineman
    12/8/21
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_UIELEMENT_HPP
#define OLYMPUS_UIELEMENT_HPP

#include <string>
#include <vector>
#include "../../Library/stb_image.hpp"

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>

// Hephaestus
#include "../../Shader/Shader.hpp"
#include "../Renderer/RenderObject.hpp"

typedef void (*Function)();

class UIElement: public RenderObject {
    Function onClick;
    Function onHover;
};


#endif //OLYMPUS_UIELEMENT_HPP
