#include "disc.h"

Disc::Disc()
    : Shape(), center(Point3f(0,0,0)), normal(Normal3f(0,0,1)), radius(0.5f)
{}

Disc::Disc(Transform tran)
    : Shape(tran)
{}

Disc::~Disc()
{}

bool Disc::getIntersection(const Ray &ray, Intersection *intersect) const
{

}
