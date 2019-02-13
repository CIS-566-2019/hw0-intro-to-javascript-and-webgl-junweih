#ifndef SPECULARREFLECTIONMATERIAL_H
#define SPECULARREFLECTIONMATERIAL_H
#include "material.h"

class SpecularReflectionMaterial : public Material
{
public:
    SpecularReflectionMaterial();

    Color3f getScatteredColor(const Intersection &intersect,
                              const Ray &ray,
                              const Scene &scene) override;
};

#endif // SPECULARREFLECTIONMATERIAL_H
