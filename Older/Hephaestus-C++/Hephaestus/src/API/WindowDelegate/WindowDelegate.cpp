//
//  WindowDelegate.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/13/21.
//

#include "WindowDelegate.hpp"

WindowDelegate::WindowDelegate() { }

void WindowDelegate::_init() {
    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    
    if (init != NULL) {
        init();
    }
}

void WindowDelegate::_destroy() {
    if (destroy != NULL) {
        destroy();
    }
}

void WindowDelegate::_tick() {
    if (tick != NULL) {
        tick();
    }
}

void WindowDelegate::_update() {
    if (update != NULL) {
        update();
    }
}

void WindowDelegate::_render() {
    if (render != NULL) {
        render();
    }
}
