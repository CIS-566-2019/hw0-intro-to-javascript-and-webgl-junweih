#include "camera.h"
using namespace std;

Camera::Camera()
    :eye(Point3f(0, 0, 10)), ref(Point3f(0, 0, 0)), worldUp(Vector3f(0, 1, 0)),
      fieldOfView(45.0), nearClip(0.1), farClip(1000), width(400.0), height(400.0)
{
    viewMat = getViewMatrix();
    invViewMat = glm::inverse(viewMat);
    projMat = getProjectionMatrix();
    invProjMat = glm::inverse(projMat);
}

//Ray Camera::rayCast(glm::vec2 pixelCooridinate) {
//    Point3f rayOrigin = eye;
//    glm::vec2 screenCoordinate = glm::vec2(pixelCooridinate.x / width * 2.0 -1.0,
//                                           1 - pixelCooridinate.y / height * 2.0);
//    Point3f p = glm::vec3(invViewMat * invProjMat * (farClip * glm::vec4(screenCoordinate.x, screenCoordinate.y, 1, 1)));
//    Vector3f rayDirection = glm::normalize(p - eye);
//    Ray outRay = Ray(rayOrigin, rayDirection);
//    return outRay;
//}

Ray Camera::rayCast(glm::vec2 pixelCooridinate) {
    glm::vec2 screenCoordinate = glm::vec2(pixelCooridinate.x / width * 2.0 -1.0,
                                               1 - pixelCooridinate.y / height * 2.0);
    float len = glm::length(ref - eye);
    Vector3f v = worldUp * len * glm::tan(glm::radians(fieldOfView/2));
    Vector3f r = glm::cross(glm::normalize(ref - eye), worldUp);
    Vector3f h = r * len * width/height * glm::tan(glm::radians(fieldOfView/2));
    Point3f p = ref + screenCoordinate.x * h + screenCoordinate.y * v;
    Point3f rayOrigin = eye;
    Vector3f rayDirection = glm::normalize(p - eye);
    Ray outRay = Ray(rayOrigin, rayDirection);
    return outRay;
}

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 m = glm::lookAt(eye, ref, worldUp);
    return m;
}

glm::mat4 Camera::getProjectionMatrix() {
    glm::mat4 m = glm::perspective(fieldOfView, width/height, nearClip, farClip);
    return m;
}
