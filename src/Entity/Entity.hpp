#pragma once

#include "../lheaders.hpp"

class Entity {
public:
    glm::vec3 transform;
    glm::vec3 scale;
    glm::vec3 color;
    bool rotateX;
    bool rotateY;
    bool rotateZ;
    float rotationDegrees;
    std::string texturePath;
};
