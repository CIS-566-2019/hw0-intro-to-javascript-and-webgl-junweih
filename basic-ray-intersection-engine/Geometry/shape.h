#ifndef SHAPE_H
#define SHAPE_H
#include "../globalincludes.h"
#include "../transform.h"
#include "../ray.h"
#include "../intersection.h"

class Intersection;
enum ShapeType :unsigned char
{
    sphere, squarePlane, noneShape
};

class Shape
{
public:
    Transform transform;
    ShapeType shapeType;

public:
    Shape();
    Shape(Transform tran);
    virtual ~Shape();
    virtual bool getIntersection(const Ray& ray, Intersection* intersect) const = 0;
};

#endif // SHAPE_H
