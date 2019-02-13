#ifndef SQUAREPLANE_H
#define SQUAREPLANE_H
#include "shape.h"


class SquarePlane : public Shape
{
public:
    Point3f center;
    float length;
    Vector3f normal;

public:
    SquarePlane();
    SquarePlane(Transform trans);
    bool getIntersection(const Ray& ray, Intersection *intersect) const override;
};

#endif // SQUAREPLANE_H
