#ifndef BLINNPHONGMATERIAL_H
#define BLINNPHONGMATERIAL_H
#include "material.h"

class BlinnPhongMaterial : public Material
{
public:
    BlinnPhongMaterial();
    Color3f getScatteredColor(const Intersection &intersect,
                              const Ray &ray,
                              const Scene &scene) override;
};

#endif // BLINNPHONGMATERIAL_H
