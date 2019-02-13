#include "sphere.h"

Sphere::Sphere()
    :center(Point3f(0, 0, 0)), radius(0.5f)
{}

Sphere::Sphere(Transform trans)
    : center(Point3f(0, 0, 0)), radius(0.5f), Shape(trans)
{}

bool Sphere::getIntersection(const Ray& ray, Intersection *intersect) const {
    if (nullptr == intersect) {
        std::cout << "Sphere getIntersection, intersect == nullptr" << std::endl;
        return false;
    }

    glm::vec3 r0 = ray.origin;
    glm::vec3 rd = ray.direction;
    glm::vec3 rc = center;
    float A = rd.x*rd.x + rd.y*rd.y + rd.z*rd.z;
    float B = 2 * (rd.x * (r0.x-rc.x) + rd.y * (r0.y-rc.y) + rd.z * (r0.z-rc.z));
    float C = std::pow(r0.x-rc.x, 2) + std::pow(r0.y-rc.y, 2) + std::pow(r0.z-rc.z, 2) - std::pow(radius,2);
    float determinate = B*B - 4*A*C;
    if (determinate < 0) {
        return false;
    }
    else {
        float intersect_t1 = (-B + glm::sqrt(determinate)) / (2 * A);
        float intersect_t2 = (-B - glm::sqrt(determinate)) / (2 * A);
        float intersect_t = glm::min(intersect_t1, intersect_t2);
        if(intersect_t < 0) {
            intersect_t = glm::max(intersect_t1, intersect_t2);
        }
        intersect->point = ray.origin + intersect_t * ray.direction;
        intersect->t = intersect_t;
        intersect->normal = glm::normalize(transform.worldTransformInverseTranspose * glm::normalize(intersect->point - center));
        return true;
    }
}
