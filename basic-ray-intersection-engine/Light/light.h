#ifndef LIGHT_H
#define LIGHT_H
#include "../globalincludes.h"
#include "../transform.h"
#include "ray.h"
class Intersection;
class Scene;

enum LightType : unsigned char
{
    pointlight, noneLight, areaLight
};

class Light
{
public:
    Color3f color;
    Point3f position;
    Vector3f direction;
    Transform transform;
    LightType lightType;

public:
    Light();
    Light(Transform trans);
    virtual Color3f shadowTest(const Intersection& intersect,
                                 const Scene& scene) = 0;
};

#endif // LIGHT_H
