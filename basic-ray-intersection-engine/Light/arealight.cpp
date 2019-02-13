#include "arealight.h"
#include "intersection.h"
#include "scene.h"

AreaLight::AreaLight()
    : Light()
{
    lightType = areaLight;
}

AreaLight::AreaLight(Transform trans)
    : Light(trans)
{
    lightType = areaLight;

}

void AreaLight::generateSample(int sampleNum, SampleMode sampleMode, WarpMethod warpMode) {
    Sampler sampler;
    sampler.generateSamples(sampleNum, sampleMode, warpMode);
    std::vector<float> m_samples = sampler.peekSamples();
    for (int i = 0; i < m_samples.size(); i = i+3) {
        Point3f newPoint(m_samples[i] - 0.5, m_samples[i+1] - 0.5, m_samples[i+2]);
        Point3f transformPoint = Point3f(transform.worldTransform * glm::vec4(newPoint,1));
        m_samplesPoint.push_back(transformPoint);
    }
}



Color3f AreaLight::shadowTest(const Intersection &intersect, const Scene &scene) {
    Color3f outColor(0, 0, 0);

    int sampleSize = m_samplesPoint.size();
    for (int i = 0; i < sampleSize; i++) {
        Point3f samplePos = m_samplesPoint[i];
        outColor = outColor + singleSampleShadowTest(intersect, scene, samplePos);
    }
    outColor = outColor / (float) sampleSize;
    return outColor;
}

Color3f AreaLight::singleSampleShadowTest(const Intersection &intersect, const Scene &scene,
                                          Point3f samplePos)
{
    Intersection* tmpIntersect = new Intersection();
    Point3f point = intersect.point;
    Vector3f point2Light = glm::normalize(samplePos - point);
    point += point2Light * 0.0001f;
    Color3f outColor(1,1,1);
    Ray ray(point, point2Light);
    float tLight2Point = -1;
    float distanceLight2Point = glm::length(samplePos - point);
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
