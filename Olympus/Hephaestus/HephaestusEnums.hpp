/*
    HephaestusEnums.hpp
    Zachary lineman
    3/17/22
    
    =================
    DESCRIPTION
    =================
*/

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

#endif //LOWDATA_HEPHAESTUSENUMS_HPP
