#ifndef SPECULARTRANSMISSIONMATERIAL_H
#define SPECULARTRANSMISSIONMATERIAL_H
#include "material.h"


class SpecularTransmissionMaterial : public Material
{

public:
    float iorIn;
    float iorOut;

public:
    SpecularTransmissionMaterial();
    SpecularTransmissionMaterial(float in, float out);

    Color3f getScatteredColor(const Intersection &intersect,
                              const Ray &ray,
                              const Scene &scene) override;
};

#endif // SPECULARTRANSMISSIONMATERIAL_H
