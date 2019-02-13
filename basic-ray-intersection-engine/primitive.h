#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "globalincludes.h"
#include <QString>
#include "Geometry/shape.h"
#include "iostream"
#include "Light/light.h"
#include "Material/material.h"

class Shape;
class Light;
class Material;

class Primitive
{
public:
    QString name;
    std::unique_ptr<Shape> shape;
    std::unique_ptr<Light> light;
    std::unique_ptr<Material> material;


public:
    Primitive();
    Primitive(QString qname, std::unique_ptr<Shape> shapePtr,
              std::unique_ptr<Light> lightPtr, std::unique_ptr<Material> materialPtr);
    bool getIntersection(const Ray& ray, Intersection* intersect) const;
};

#endif // PRIMITIVE_H
