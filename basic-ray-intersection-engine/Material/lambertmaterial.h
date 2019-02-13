#ifndef LAMBERTMATERIAL_H
#define LAMBERTMATERIAL_H
#include "material.h"

class LambertMaterial : public Material
{
public:
    LambertMaterial();

    Color3f getScatteredColor(const Intersection &intersect,
                              const Ray &ray,
                              const Scene &scene) override;
};

#endif // LAMBERTMATERIAL_H
