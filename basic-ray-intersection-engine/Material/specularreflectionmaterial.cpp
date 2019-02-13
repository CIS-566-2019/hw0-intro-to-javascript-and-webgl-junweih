#include "specularreflectionmaterial.h"
#include "scene.h"

SpecularReflectionMaterial::SpecularReflectionMaterial()
    : Material()
{
    materialType = specRefl;
}

Color3f SpecularReflectionMaterial::getScatteredColor(const Intersection &intersect,
                                                      const Ray &ray, const Scene &scene)
{
    if (scene.iterTimes++ > scene.iterMax) {
        return intersect.objectHit->material->color;
    }

    Vector3f v = ray.direction;
    Normal3f n = intersect.normal;
    Vector3f r = glm::reflect(v, n);
    float epsilon = 0.0001;
    Ray reflectedRay = Ray(intersect.point + intersect.normal * epsilon, r);

    Intersection *tmpIntersect = new Intersection();
    Color3f outColor = intersect.objectHit->material->color;
    if (scene.getIntersection(reflectedRay, tmpIntersect)) {
        outColor =  outColor * tmpIntersect->objectHit->material->getScatteredColor(*tmpIntersect, reflectedRay, scene);
    }
    else {
        outColor = Color3f(0,0,0) ;
    }
    float coeffi = 1.5f;
    return glm::clamp(coeffi * outColor, Color3f(0,0,0), Color3f(1,1,1));
}
