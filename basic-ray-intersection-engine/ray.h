#ifndef RAY_H
#define RAY_H
#include "globalincludes.h"

class Ray
{
public:
    Point3f origin;
    Vector3f direction;

public:
    Ray();
    Ray(Point3f ori, Vector3f dir);
    Ray transformRay(glm::mat4 transformMatrix);
};

#endif // RAY_H
