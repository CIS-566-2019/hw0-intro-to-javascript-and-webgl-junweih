#ifndef AREALIGHT_H
#define AREALIGHT_H
#include "light.h"
#include "sampler.h"

class AreaLight : public Light
{
public:
    Point3f center;
    Normal3f normal;
    std::vector<Point3f> m_samplesPoint;

public:
    AreaLight();
    AreaLight(Transform trans);
    Color3f shadowTest(const Intersection &intersect, const Scene &scene) override;
    void generateSample(int sampleNum, SampleMode sampleMode, WarpMethod warpMode);
    Color3f singleSampleShadowTest(const Intersection &intersect,
                                   const Scene& scene, Point3f samplePos);
};

#endif // AREALIGHT_H
