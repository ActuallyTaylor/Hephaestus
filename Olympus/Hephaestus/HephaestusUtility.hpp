/*
    HephaestusEnums.hpp
    Zachary lineman
    3/17/22
    
    =================
    DESCRIPTION
    =================
*/

#import <random>
#import <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define HEPHAESTUS_ANY_KEY      314901

#ifndef LOWDATA_HEPHAESTUSENUMS_HPP
#define LOWDATA_HEPHAESTUSENUMS_HPP

enum ScreenAnchor { topLeft, topCenter, topRight, centerLeft, center, centerRight, bottomLeft, bottomCenter, bottomRight };
enum PositioningType { absolute, relative };
enum AnchorPoint { pointTopLeft, pointTopCenter, pointTopRight, pointCenterLeft, pointCenter, pointCenterRight, pointBottomLeft, pointBottomCenter, pointBottomRight };
enum SamplingType { nearest, linear, nearestMipMapNearest, linearMipMapNearest, nearestMipmapLinear, linearMipmapLinear};

inline GLint translateSamplingType(SamplingType samplingType) {
    switch(samplingType) {
        case nearest:
            return GL_NEAREST;
        case linear:
            return GL_LINEAR;
        case nearestMipMapNearest:
            return GL_NEAREST_MIPMAP_NEAREST;
        case linearMipMapNearest:
            return GL_LINEAR_MIPMAP_NEAREST;
        case nearestMipmapLinear:
            return GL_NEAREST_MIPMAP_LINEAR;
        case linearMipmapLinear:
            return GL_LINEAR_MIPMAP_LINEAR;
    }
};

template <typename T>
int indexOf(T object, std::vector<T> vector) {
    for (int n = 0; n < vector.capacity(); n++) {
        if (vector[n] == object) {
            return n;
        }
    }
    return -1;
}

static int generateID() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distr(0, INT_MAX - 1);
    return distr(mt);
}

static float randomFloat() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(mt);
}

static int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(mt);
}

static int randomWeightedInt(std::initializer_list<double> weights,  std::initializer_list<int> numbers) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d(weights);
    std::map<int, int> map;
    int index = d(gen);
    return numbers.begin()[index];
}

#endif //LOWDATA_HEPHAESTUSENUMS_HPP
