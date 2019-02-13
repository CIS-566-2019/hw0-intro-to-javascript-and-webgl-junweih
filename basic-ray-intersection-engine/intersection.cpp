#include "intersection.h"

Intersection::Intersection()
    :point(Point3f(0,0,0)), normal(Normal3f(0,0,0)), t(0.f), objectHit(nullptr)
{

}

Intersection::~Intersection() {
    delete objectHit;
}

Intersection::Intersection(Point3f point1, Normal3f normal1, float t1)
    : point(point1), normal(normal1), t(t1), objectHit(nullptr)
{

}
