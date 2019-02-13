#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "globalincludes.h"
#include "primitive.h"

class Primitive;

class Intersection
{
public:
    Point3f point;
    Normal3f normal;
    float t;
    const Primitive* objectHit;

public:
    Intersection();
    ~Intersection();
    Intersection(Point3f point1, Normal3f normal1, float t1);
};

#endif // INTERSECTION_H
