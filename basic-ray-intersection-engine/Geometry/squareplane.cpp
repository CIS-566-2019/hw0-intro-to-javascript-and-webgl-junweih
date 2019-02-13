#include "squareplane.h"

SquarePlane::SquarePlane()
    : center(Point3f(0, 0, 0)), length(1), normal(Normal3f(0, 0, 1))
{}

SquarePlane::SquarePlane(Transform trans)
    : center(Point3f(0, 0, 0)), length(1), normal(Normal3f(0, 0, 1)), Shape(trans)
{}

bool SquarePlane::getIntersection(const Ray& ray, Intersection *intersect) const{
    float t = glm::dot(normal, (center - ray.origin)) / glm::dot(normal, ray.direction);
    Point3f point = ray.origin + t * ray.direction;
    if (point.x < -0.5 || point.x > 0.5 || point.y < -0.5 || point.y > 0.5) {
        return false;
    }
    else {

        intersect->normal = glm::normalize(transform.worldTransformInverseTranspose * glm::normalize(normal));
        intersect->point = point;
        intersect->t = t;
        Primitive* object = new Primitive();
        object->name = "Square Plane";
        std::unique_ptr<SquarePlane> squarePlaneObject;
        object->shape = std::move(squarePlaneObject);
        intersect->objectHit = object;
        return true;
    }
}
