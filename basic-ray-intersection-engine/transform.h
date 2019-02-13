#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "globalincludes.h"


class Transform
{
public:
    glm::vec3 translation;
    glm::vec3 scale;
    glm::vec3 rotation;
    glm::mat4 worldTransform;
    glm::mat4 WorldTransformInverse;
    glm::mat3 worldTransformInverseTranspose;

public:
    Transform();
    Transform(glm::vec3 translation_, glm::vec3 rotation_, glm::vec3 scale_);
};

#endif // TRANSFORM_H
