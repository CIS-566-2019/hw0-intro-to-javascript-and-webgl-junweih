#include "transform.h"

Transform::Transform()
    : translation(glm::vec3(0,0,0)), rotation(glm::vec3(0,0,0)), scale(glm::vec3(0,0,0)),
      worldTransform(glm::mat4(1.f)), WorldTransformInverse(glm::mat4(1.f)),
      worldTransformInverseTranspose(glm::mat4(1.f))
{}

Transform::Transform(glm::vec3 translation_, glm::vec3 rotation_, glm::vec3 scale_)
    :   translation(translation_), rotation(rotation_), scale(scale_)
{
    worldTransform = glm::translate(glm::mat4(1.0f), translation) *
                    glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1,0,0)) *
                    glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0,1,0)) *
                    glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0,0,1)) *
                    glm::scale(glm::mat4(1.0f), scale);
    WorldTransformInverse = glm::inverse(worldTransform);
    worldTransformInverseTranspose = glm::mat3( glm::transpose(WorldTransformInverse) );
}
