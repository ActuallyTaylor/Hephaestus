//
//  WindowDelegate.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/13/21.
//

#ifndef WindowDelegate_hpp
#define WindowDelegate_hpp

#include <stdio.h>

// Include GLEW & GLFW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef void (*Function)();

class WindowDelegate {
public:
    WindowDelegate();

    Function init, destroy, tick, update, render;

    void _init ();
    void _destroy ();
    void _tick ();
    void _update ();
    void _render ();
};

#endif /* WindowDelegate_hpp */
