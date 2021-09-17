//
//  CompressedData.hpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#ifndef CompressedData_hpp
#define CompressedData_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector3.hpp"

using namespace std;

struct CompressedData {
    CompressedData(vector<GLfloat> vertices, vector<unsigned int> indexes);
    vector<GLfloat> vertices;
    vector<unsigned int> indexes;
};

#endif /* CompressedData_hpp */
