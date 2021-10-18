//
//  Controls.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/19/21.
//

#ifndef Controls_hpp
#define Controls_hpp

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

#include "Keybind.hpp"
 
using namespace std;

class Controls {
public:
    Controls();
    
    /*
     Variables
     */
    vector<Keybind> keybindings;
    
    /*
     Functions
     */
    void addKeybind(Keybind keybind);
    
    void executeKeybinds(int keycode, int action);
};

#endif /* Controls_hpp */
