#ifndef CAMERA_H
#define CAMERA_H
#include "globalincludes.h"
#include "ray.h"
#include "iostream"

class Camera
{
public:
    Point3f eye;
    Point3f ref;
    Vector3f worldUp;
    float fieldOfView;
    float nearClip;
    float farClip;
    float width;
    float height;
    glm::mat4 viewMat;
    glm::mat4 invViewMat;
    glm::mat4 projMat;
    glm::mat4 invProjMat;

private:

public:
    Camera();
    Ray rayCast(glm::vec2 pixelCooridinate);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};

#endif // CAMERA_H
