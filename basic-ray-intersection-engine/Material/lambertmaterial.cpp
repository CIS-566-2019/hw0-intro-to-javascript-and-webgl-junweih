#include "lambertmaterial.h"
#include "scene.h"

LambertMaterial::LambertMaterial()
    : Material()
{
    materialType = lambert;
}

Color3f LambertMaterial::getScatteredColor(const Intersection &intersect, const Ray &ray,
                                           const Scene &scene)
{
    Color3f outColor(0,0,0);

    int sceneSize = scene.m_primitives.size();
    Color3f passLight (1,1,1);

    for (int i = 0; i < sceneSize; i++) {
        if (nullptr == scene.m_primitives[i]->light) {
            continue;
        }

        passLight = scene.m_primitives[i]->light->shadowTest(intersect, scene);
        Intersection* tmpIntersect = new Intersection();
        Ray backRay = Ray(intersect.point, -ray.direction);
        if (scene.getIntersection(backRay, tmpIntersect, 2)) {
            passLight = passLight * tmpIntersect->objectHit->material->color;
        }


        float diffuseCoeffi = 1.0;
        Color3f diffuseColor = diffuseCoeffi * scene.m_primitives[i]->light->color * this->color *
                            passLight *
                            glm::dot(glm::normalize(intersect.normal),
                                     glm::normalize(scene.m_primitives[i]->light->position - intersect.point));

        outColor = glm::clamp(outColor + diffuseColor, Color3f(0,0,0), Color3f(1,1,1));
    }

    return outColor;
}
