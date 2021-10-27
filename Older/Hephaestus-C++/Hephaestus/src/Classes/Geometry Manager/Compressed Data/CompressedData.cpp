//
//  CompressedData.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/17/21.
//

#include "CompressedData.hpp"

CompressedData::CompressedData(vector<GLfloat> vertices, vector<unsigned int> indexes) {
    this->vertices = vertices;
    this->indexes = indexes;
}
