#ifndef DISC_H
#define DISC_H
#include "shape.h"

class Disc : public Shape
{
public:
    Point3f center;
    Normal3f normal;
    float radius;

public:
    Disc();
    Disc(Transform tran);
    ~Disc();
    bool getIntersection(const Ray &ray, Intersection *intersect) const override;
};

#endif // DISC_H
