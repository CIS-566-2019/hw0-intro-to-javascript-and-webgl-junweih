#ifndef MATERIAL_H
#define MATERIAL_H
#include "globalincludes.h"
#include <memory>
class Primitive;
class Intersection;
class Scene;
class Primitive;
class Ray;
enum MaterialType : unsigned char
{
    noneMaterial, blinn, lambert, specRefl, specTrans
};

class Material
{
public:
    Color3f color;
    MaterialType materialType;

public:
    Material();
    virtual Color3f getScatteredColor(const Intersection& intersect,
                                        const Ray& ray,
                                        const Scene& scene) = 0;
};

#endif // MATERIAL_H
