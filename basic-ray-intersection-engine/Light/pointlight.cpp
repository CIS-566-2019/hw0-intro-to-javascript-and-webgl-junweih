#include "pointlight.h"
#include "intersection.h"
#include "scene.h"

PointLight::PointLight()
    : Light()
{
    lightType = pointlight;
}

PointLight::PointLight(Transform trans)
    : Light(trans)
{
    lightType = pointlight;
}

Color3f PointLight::shadowTest(const Intersection &intersect, const Scene &scene) {
    Intersection* tmpIntersect = new Intersection();
    Point3f point = intersect.point;
    Vector3f point2Light = glm::normalize(this->position - point);
    point += point2Light * 0.0001f;
    Color3f outColor(1,1,1);
    Ray ray(point, point2Light);
    float tLight2Point = -1;
    float distanceLight2Point = glm::length(this->position - point);
    // intersect only with opaque primitive
    if (scene.getIntersection(ray, tmpIntersect, 1)) {
        tLight2Point = tmpIntersect->t;
        if (tLight2Point < distanceLight2Point && tLight2Point > 0) {
            return Color3f(0,0,0);
        }
    }
    // intersect only with tranparency primitive
    if (scene.getIntersection(ray, tmpIntersect, 2)) {
        tLight2Point = tmpIntersect->t;
        if (tLight2Point < distanceLight2Point && tLight2Point > 0) {
            return tmpIntersect->objectHit->material->color * shadowTest(*tmpIntersect, scene);
        }
    }

    return outColor;
}
