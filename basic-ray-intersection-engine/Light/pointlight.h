#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "light.h"


class PointLight : public Light
{
public:
    PointLight();
    PointLight(Transform trans);
    Color3f shadowTest(const Intersection &intersect, const Scene &scene) override;
};

#endif // POINTLIGHT_H
