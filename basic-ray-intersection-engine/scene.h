#ifndef SCENE_H
#define SCENE_H
#include "globalincludes.h"
#include "QList"
#include "primitive.h"
#include "ray.h"
#include "intersection.h"
#include "Geometry/shape.h"
#include "Geometry/sphere.h"
#include "Geometry/squareplane.h"
#include "Geometry/disc.h"
#include "Light/light.h"
#include "Light/pointlight.h"
#include "Light/arealight.h"
#include "Material/material.h"
#include "Material/blinnphongmaterial.h"
#include "Material/lambertmaterial.h"
#include "Material/specularreflectionmaterial.h"
#include "Material/speculartransmissionmaterial.h"
#include <memory>
#include "camera.h"


class Scene
{
public:
    std::vector<std::unique_ptr<Primitive>> m_primitives;
    Camera camera;
    static int iterTimes;
    static int iterMax;
public:
    Scene();
    // 0 = intersect with all primitive
    // 1 = intersect with only opaque primitive
    // 2 = intersect with only transparency primitive
    bool getIntersection(const Ray& ray, Intersection* intersect, int testShadow = 0) const;
    void setScene1();
    void setScene2();
    void setSceneLambert();
    void setSceneRefl();
    void setSceneTwoLights();
    void setSceneAreaLight();
    void addLightPrimitive(QString name, ShapeType shapeType,
                           LightType lightType,
                           Transform transform,
                           Color3f lightColor, int numSample,
                           SampleMode sampleMode, WarpMethod warpMethod);
    void addPrimitive(QString name, ShapeType shapeType,
                      LightType lightType,
                      MaterialType materialType,
                      Transform transform,
                      Color3f lightColor,Color3f geoColor,
                      float iorIn = 0, float iorOut = 0);
    void setCamera(Point3f eye, Point3f ref, Point3f worldUp,
                   float fieldOfView,float width, float height,
                   float nearClip = 0.1, float farClip = 1000);
};

#endif // SCENE_H
