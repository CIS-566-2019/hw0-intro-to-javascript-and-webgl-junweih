#include "speculartransmissionmaterial.h"
#include "scene.h"

SpecularTransmissionMaterial::SpecularTransmissionMaterial()
    :Material(), iorIn(0), iorOut(0)
{
    materialType = specTrans;
}

SpecularTransmissionMaterial::SpecularTransmissionMaterial(float in, float out)
    :Material(), iorIn(in), iorOut(out)
{
    materialType = specTrans;
}

Color3f SpecularTransmissionMaterial::getScatteredColor(const Intersection &intersect,
                                                        const Ray &ray, const Scene &scene)
{
    Color3f baseColor = intersect.objectHit->material->color;
    if (scene.iterTimes++ > scene.iterMax) {
        return baseColor;
    }
    Vector3f v = ray.direction;
    Normal3f n = intersect.normal;
    Vector3f r;
    Ray reflectedRay;
    float epsilon = 0.001;

    if (glm::dot(v, n) >= 0){
        r = glm::refract(v, -n, this->iorIn / this->iorOut);
        if (glm::length(r) == 0) {
            r = glm::reflect(v, -n);
        }
        reflectedRay = Ray(intersect.point + epsilon * intersect.normal, r);
    }
    else {
        r = glm::refract(v, n, this->iorOut / this->iorIn);
        if (glm::length(r) == 0) {
            r = glm::reflect(v, n);
        }
        reflectedRay = Ray(intersect.point - epsilon * intersect.normal, r);
    }

    Intersection *tmpIntersect = new Intersection();
    Color3f outColor = baseColor;
    if (scene.getIntersection(reflectedRay, tmpIntersect, 0)) {
        outColor = outColor * tmpIntersect->objectHit->material->getScatteredColor(*tmpIntersect, reflectedRay, scene);
    }
    else{
        outColor = Color3f(0,0,0);
    }

    return outColor;
}
