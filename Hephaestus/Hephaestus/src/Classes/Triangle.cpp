//
//  Triangle.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 9/11/21.
//

#include "Triangle.hpp"


Triangle::Triangle (GLfloat vertices[9], int vboNumb) {
    GLuint vbo = vboNumb;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    GLuint vao = vboNumb;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

}

void Triangle::Draw() {
    int vertMax = id * 3;
    glDrawArrays(GL_TRIANGLES, vertMax - 3, vertMax);
}
