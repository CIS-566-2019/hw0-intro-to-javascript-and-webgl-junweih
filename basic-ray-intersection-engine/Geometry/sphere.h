#ifndef SPHERE_H
#define SPHERE_H
#include "shape.h"
#include "iostream"

class Sphere : public Shape
{
public:
    Point3f center;
    float radius;
public:
    Sphere();
    Sphere(Transform trans);
    bool getIntersection(const Ray& ray, Intersection *intersect) const override;
};

#endif // SPHERE_H
