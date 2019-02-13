#include "blinnphongmaterial.h"
#include "scene.h"


BlinnPhongMaterial::BlinnPhongMaterial()
    : Material()
{
    materialType = blinn;
}

Color3f BlinnPhongMaterial::getScatteredColor(const Intersection &intersect, const Ray &ray,
                                              const Scene &scene)
{
    Color3f outColor(0,0,0);
    Color3f passLight(1,1,1);
    int sceneSize = scene.m_primitives.size();
    for (int i = 0; i < sceneSize; i++){
        if (nullptr == scene.m_primitives[i]->light) {
            continue;
        }

        passLight = scene.m_primitives[i]->light->shadowTest(intersect, scene);

        float diffuseCoeffi = 1.0f;
        Color3f diffuseColor = diffuseCoeffi * scene.m_primitives[i]->light->color * this->color *
                            passLight *
                            glm::dot(glm::normalize(intersect.normal),
                                     glm::normalize(scene.m_primitives[i]->light->position - intersect.point));

        float specularCoeffi = 0.5f;
        float shiness = 10;

        glm::vec3 eye = glm::normalize(scene.camera.eye - intersect.point);
        glm::vec3 light = glm::normalize(scene.m_primitives[i]->light->position - intersect.point);
        glm::vec3 norm = glm::normalize(intersect.normal);
        glm::vec3 h_vec = glm::normalize(eye + light);
        float s = glm::max(glm::pow(glm::dot(h_vec, norm), shiness), 0.0f);
        Color3f specularColor = s * glm::vec3(specularCoeffi);

        outColor = glm::clamp(outColor + diffuseColor + specularColor, Color3f(0,0,0), Color3f(1,1,1));
    }
    return outColor;
}
