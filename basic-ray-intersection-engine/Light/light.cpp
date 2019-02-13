#include "light.h"
#include "../transform.h"
Light::Light()
    :color(Color3f(1, 1, 1)), position(Point3f(0, 0, 0)), direction(Vector3f(1, 0, 0)), transform()
{

}

Light::Light(Transform trans)
    :color(Color3f(1, 1, 1)), transform(trans)
{
    position = Point3f(trans.worldTransform * glm::vec4(Point3f(0), 1.f));
    direction = Vector3f(trans.worldTransform * glm::vec4(Vector3f(0, 0, -1), 0));
}
