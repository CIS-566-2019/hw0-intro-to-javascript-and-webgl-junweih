#include "ray.h"

Ray::Ray()
    :origin(Point3f(0,0,0)), direction(Vector3f(0,0,1))
{

}

Ray::Ray(Point3f ori, Vector3f dir)
    :origin(ori), direction(dir)
{

}

Ray Ray::transformRay(glm::mat4 transformMatrix) {
    glm::vec4 origin4D = transformMatrix *
                        glm::vec4(origin.x, origin.y, origin.z, 1);
    glm::vec4 direction4D = transformMatrix *
                            glm::vec4(direction.x, direction.y, direction.z, 0);
//    glm::vec4 origin4D = glm::inverse(transformMatrix) *
//                        glm::vec4(origin.x, origin.y, origin.z, 1);
//    glm::vec4 direction4D = glm::inverse(transformMatrix) *
//                            glm::vec4(direction.x, direction.y, direction.z, 0);
    Ray outRay = Ray(Point3f(origin4D.x, origin4D.y, origin4D.z),
                         Vector3f(direction4D.x, direction4D.y, direction4D.z));

    return outRay;
}
