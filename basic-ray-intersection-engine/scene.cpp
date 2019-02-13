#include "scene.h"

int Scene::iterMax = 5;
int Scene::iterTimes = 0;

Scene::Scene()

{
    camera = Camera();
}

void Scene::setCamera(Point3f eye, Point3f ref, Point3f worldUp,
                      float fieldOfView, float width, float height,
                      float nearClip, float farClip)
{
    camera.eye = eye;
    camera.ref = ref;
    camera.worldUp = worldUp;
    camera.fieldOfView = fieldOfView;
    camera.nearClip = nearClip;
    camera.farClip = farClip;
    camera.width = width;
    camera.height = height;
}

void Scene::addLightPrimitive(QString name, ShapeType shapeType,
                              LightType lightType, Transform transform,
                              Color3f lightColor, int numSample,
                              SampleMode sampleMode, WarpMethod warpMethod)
{
    Primitive* rawPrimitive = new Primitive();
    std::unique_ptr<Primitive> primitivePtr (rawPrimitive);
    primitivePtr->name = name;

    switch (shapeType) {
    case ShapeType::sphere:
    {
        Sphere* rawSphere = new Sphere(transform);
        std::unique_ptr<Sphere> spherePtr(rawSphere);
        primitivePtr->shape = std::move(spherePtr);
    }
        break;
    case ShapeType::squarePlane:
    {
        SquarePlane* rawPlane = new SquarePlane(transform);
        std::unique_ptr<SquarePlane> planePtr(rawPlane);
        primitivePtr->shape = std::move(planePtr);
    }
        break;
    default:
        primitivePtr->shape = nullptr;
        break;
    }

    // light
    switch (lightType) {
    case LightType::pointlight:
    {
        PointLight* rawPointLight = new PointLight(transform);
        std::unique_ptr<PointLight> pointLightPtr(rawPointLight);
        primitivePtr->light = std::move(pointLightPtr);
    }
        break;
    case LightType::areaLight:
    {
        AreaLight* rawAreaLight = new AreaLight(transform);

        std::unique_ptr<AreaLight> areaLightPtr(rawAreaLight);

        areaLightPtr->generateSample(numSample, sampleMode, warpMethod);
        primitivePtr->light = std::move(areaLightPtr);
    }
        break;
    default:
        primitivePtr->light = nullptr;
        break;
    }
    if (nullptr != primitivePtr->light) {
        primitivePtr->light->color = lightColor;
    }
    primitivePtr->material = nullptr;

    m_primitives.push_back(std::move(primitivePtr));
}

void Scene::addPrimitive(QString name, ShapeType shapeType,
                         LightType lightType,
                         MaterialType materialType,
                         Transform transform, Color3f lightColor, Color3f geoColor, float iorIn, float iorOut)
{
    Primitive* rawPritimitive = new Primitive();
    std::unique_ptr<Primitive> primitivePtr (rawPritimitive);
    primitivePtr->name = name;


    switch (shapeType) {
    case ShapeType::sphere:
    {
        Sphere* rawSphere = new Sphere(transform);
        std::unique_ptr<Sphere> spherePtr(rawSphere);
        primitivePtr->shape = std::move(spherePtr);
    }
        break;
    case ShapeType::squarePlane:
    {
        SquarePlane* rawPlane = new SquarePlane(transform);
        std::unique_ptr<SquarePlane> planePtr(rawPlane);
        primitivePtr->shape = std::move(planePtr);
    }
        break;
    default:
        primitivePtr->shape = nullptr;
        break;
    }

    // light
    switch (lightType) {
    case LightType::pointlight:
    {
        PointLight* rawPointLight = new PointLight(transform);
        std::unique_ptr<PointLight> pointLightPtr(rawPointLight);
        primitivePtr->light = std::move(pointLightPtr);
    }
        break;
    case LightType::areaLight:
    {
        AreaLight* rawAreaLight = new AreaLight(transform);
        std::unique_ptr<AreaLight> areaLightPtr(rawAreaLight);
        primitivePtr->light = std::move(areaLightPtr);
    }
        break;
    default:
        primitivePtr->light = nullptr;
        break;
    }


    // material
    switch (materialType) {
    case MaterialType::blinn:
    {
        BlinnPhongMaterial* rawBlinn = new BlinnPhongMaterial();
        std::unique_ptr<BlinnPhongMaterial> blinnPtr(rawBlinn);
        primitivePtr->material = std::move(blinnPtr);
    }
        break;
    case MaterialType::lambert:
    {
        LambertMaterial* rawLambert = new LambertMaterial();
        std::unique_ptr<LambertMaterial> lambertPtr(rawLambert);
        primitivePtr->material = std::move(lambertPtr);
    }
        break;
    case MaterialType::specRefl:
    {
        SpecularReflectionMaterial* rawSpecRefl = new SpecularReflectionMaterial();
        std::unique_ptr<SpecularReflectionMaterial> specReflPtr(rawSpecRefl);
        primitivePtr->material = std::move(specReflPtr);
    }
        break;
    case MaterialType::specTrans:
    {
        SpecularTransmissionMaterial* rawSpecTran = new SpecularTransmissionMaterial(iorIn, iorOut);
        std::unique_ptr<SpecularTransmissionMaterial> specTranPtr(rawSpecTran);
        primitivePtr->material = std::move(specTranPtr);
    }
        break;
    default:
        primitivePtr->material = nullptr;
        break;
    }

    if (nullptr != primitivePtr->light) {
        primitivePtr->light->color = lightColor;
    }
    if (nullptr != primitivePtr->material) {
        primitivePtr->material->color = geoColor;
    }
    m_primitives.push_back(std::move(primitivePtr));
}

void Scene::setScene1() {
    addPrimitive("Sphere0", ShapeType::sphere, LightType::noneLight,
                 MaterialType::noneMaterial, Transform(glm::vec3(-1, 1, 0),
                                                         glm::vec3(0, 0, 0),
                                                         glm::vec3(2, 4, 2)),
                 Color3f(0,0,0), Color3f(1,1,1));
    addPrimitive("Plane0", ShapeType::squarePlane, LightType::noneLight,
                 MaterialType::noneMaterial, Transform(glm::vec3(0, 0, -5),
                                                         glm::vec3(0, 30, 0),
                                                         glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));
}

void Scene::setScene2() {
    addPrimitive("Sphere0", ShapeType::sphere, LightType::noneLight,
                 MaterialType::noneMaterial, Transform(glm::vec3(0, 0, 1),
                                                         glm::vec3(0, 0, 45),
                                                         glm::vec3(2, 1, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));
    addPrimitive("Sphere1", ShapeType::sphere, LightType::noneLight,
                 MaterialType::noneMaterial, Transform(glm::vec3(0.25, 0, 0),
                                                         glm::vec3(0, 0, 0),
                                                         glm::vec3(0.5, 0.5, 5)),
                 Color3f(0,0,0), Color3f(1,1,1));
    addPrimitive("SquarePlane0", ShapeType::squarePlane, LightType::noneLight,
                 MaterialType::noneMaterial, Transform(glm::vec3(0, -0.5, 0),
                                                         glm::vec3(90, 0, 0),
                                                         glm::vec3(5, 5, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

}

void Scene::setSceneLambert(){
    Point3f eye(0, 0.5, 12);
    Vector3f ref(0, 0, 0);
    Vector3f worldUp(0, 1, 0);
    float fov = 50.0;
    float width = 400;
    float height = 400;
    setCamera(eye, ref, worldUp, fov, width, height);

    //point light1
    addPrimitive("point light1", ShapeType::noneShape, LightType::pointlight,
                 MaterialType::noneMaterial, Transform(glm::vec3(0, 4.9, 0),
                                           glm::vec3(45, 0, 0),
                                           glm::vec3(0.5, 0.5, 0.5)),
                 1.f * Color3f(1,1,1), Color3f(0,0,0));

    //white diffuse
    addPrimitive("Back Wall", ShapeType::squarePlane, LightType::noneLight,
                 lambert ,Transform(glm::vec3(0, 0, -5),
                                               glm::vec3(0, 0, 0),
                                               glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));
    //green diffuse
    addPrimitive("Right Wall", ShapeType::squarePlane, LightType::noneLight,
                 lambert, Transform(glm::vec3(5, 0, 0),
                                               glm::vec3(0, -90, 0),
                                               glm::vec3(10, 10, 1)),
                  Color3f(0,0,0), Color3f(0,1,0));

    // red diffuse
    addPrimitive("Left Wall", ShapeType::squarePlane, LightType::noneLight,
                 lambert, Transform(glm::vec3(-5, 0, 0),
                                                 glm::vec3(0, 90, 0),
                                                 glm::vec3(10,10,1)),
                  Color3f(0,0,0), Color3f(1,0,0));

    //black_diffuse
    addPrimitive("ceiling", ShapeType::squarePlane, LightType::noneLight,
                  lambert, Transform(glm::vec3(0, 5, 0),
                                                 glm::vec3(90, 0, 0),
                                                 glm::vec3(10, 10, 1)),
                  Color3f(0,0,0), Color3f(0,0,0));

    //white_diffuse
    addPrimitive("Floor", ShapeType::squarePlane, LightType::noneLight,
                 lambert, Transform(glm::vec3(0, -5, 0),
                                                glm::vec3(-90, 0, 0),
                                                glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //purple_specular
    addPrimitive("Shiny Sphere", ShapeType::sphere, LightType::noneLight,
                 MaterialType::lambert, Transform(glm::vec3(-2, -5, 0),
                                                             glm::vec3(0, 0, 0),
                                                             glm::vec3(5, 5, 5)),
                 Color3f(0,0,0), Color3f(0.75, 0.0, 0.75));

    //refractive_specular
    addPrimitive("Transparent Sphere 1", ShapeType::sphere, LightType::noneLight,
                 lambert, Transform(glm::vec3(-3, 0, 2),
                                                             glm::vec3(0, 0, 0),
                                                             glm::vec3(4, 4, 4)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //air_bubble_mat
    addPrimitive("Inside Transparent Sphere 1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(-3, 0, 2),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(2.5, 2.5, 2.5)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //refractive_specular2
    addPrimitive("Transparent Sphere Green", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, -2, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(4, 4, 4)),
                 Color3f(0,0,0), Color3f(0.15, 1, 0.15));

    //white_diffuse
    addPrimitive("Inside Opaque 1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, -2, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //mirrored_specular2
    addPrimitive("Reflective Sphere Blue1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(-3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(3, 3, 3)),
                 Color3f(0,0,0), Color3f(0.25,0.5,1));

    //refractive_specular
    addPrimitive("Transparent Sphere 3", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(3, 3, 3)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //mirrored_specular2
    addPrimitive("Reflective Sphere Blue2", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(0.25,0.5,1));

    //yellow_diffuse
    addPrimitive("Yellow Sphere", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(0, 0, 0),
                                                    glm::vec3(0, 0, 0),
                                                    glm::vec3(2, 2, 2)),
                 Color3f(0,0,0), Color3f(1, 1, 0.25));

}

void Scene::setSceneTwoLights() {
    Point3f eye(0, 0.5, 12);
    Vector3f ref(0, 0, 0);
    Vector3f worldUp(0, 1, 0);
    float fov = 50.0;
    float width = 400;
    float height = 400;
    setCamera(eye, ref, worldUp, fov, width, height);

    //point light1
    addPrimitive("point light1", ShapeType::noneShape, LightType::pointlight,
                 MaterialType::noneMaterial, Transform(glm::vec3(-2, 4.9, 0),
                                           glm::vec3(45, 0, 0),
                                           glm::vec3(0.5, 0.5, 0.5)),
                 0.3f * Color3f(1, 0.5, 0.5), Color3f(0,0,0));

    //point light2
    addPrimitive("point light2", ShapeType::noneShape, LightType::pointlight,
                 MaterialType::noneMaterial, Transform(glm::vec3(2, 4.9, 0),
                                           glm::vec3(45, 0, 0),
                                           glm::vec3(0.5, 0.5, 0.5)),
                 0.3f * Color3f(0.5, 1, 0.5), Color3f(0,0,0));


    //white diffuse
    addPrimitive("Back Wall", ShapeType::squarePlane, LightType::noneLight,
                 lambert ,Transform(glm::vec3(0, 0, -5),
                                       glm::vec3(0, 0, 0),
                                       glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));
    //green diffuse
    addPrimitive("Right Wall", ShapeType::squarePlane, LightType::noneLight,
                 lambert, Transform(glm::vec3(5, 0, 0),
                                       glm::vec3(0, -90, 0),
                                       glm::vec3(10, 10, 1)),
                  Color3f(0,0,0), Color3f(0,1,0));

    // red diffuse
    addPrimitive("Left Wall", ShapeType::squarePlane, LightType::noneLight,
                 lambert, Transform(glm::vec3(-5, 0, 0),
                                         glm::vec3(0, 90, 0),
                                         glm::vec3(10,10,1)),
                  Color3f(0,0,0), Color3f(1,0,0));

    //black_diffuse
    addPrimitive("ceiling", ShapeType::squarePlane, LightType::noneLight,
                  lambert, Transform(glm::vec3(0, 5, 0),
                                         glm::vec3(90, 0, 0),
                                         glm::vec3(10, 10, 1)),
                  Color3f(0,0,0), Color3f(0,0,0));

    //white_diffuse
    addPrimitive("Floor", ShapeType::squarePlane, LightType::noneLight,
                 lambert, Transform(glm::vec3(0, -5, 0),
                                            glm::vec3(-90, 0, 0),
                                            glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //purple_specular
    addPrimitive("Shiny Sphere", ShapeType::sphere, LightType::noneLight,
                 MaterialType::lambert, Transform(glm::vec3(-2, -5, 0),
                                                     glm::vec3(0, 0, 0),
                                                     glm::vec3(5, 5, 5)),
                 Color3f(0,0,0), Color3f(0.75, 0.0, 0.75));

    //refractive_specular
    addPrimitive("Transparent Sphere 1", ShapeType::sphere, LightType::noneLight,
                 lambert, Transform(glm::vec3(-3, 0, 2),
                                         glm::vec3(0, 0, 0),
                                         glm::vec3(4, 4, 4)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //air_bubble_mat
    addPrimitive("Inside Transparent Sphere 1", ShapeType::sphere, LightType::noneLight,
                  lambert, Transform(glm::vec3(-3, 0, 2),
                                              glm::vec3(0, 0, 0),
                                              glm::vec3(2.5, 2.5, 2.5)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //refractive_specular2
    addPrimitive("Transparent Sphere Green", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, -2, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(4, 4, 4)),
                 Color3f(0,0,0), Color3f(0.15, 1, 0.15));

    //white_diffuse
    addPrimitive("Inside Opaque 1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, -2, -3),
                                                      glm::vec3(0, 0, 0),
                                                      glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //mirrored_specular2
    addPrimitive("Reflective Sphere Blue1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(-3, 3.5, -3),
                                                      glm::vec3(0, 0, 0),
                                                      glm::vec3(3, 3, 3)),
                 Color3f(0,0,0), Color3f(0.25,0.5,1));

    //refractive_specular
    addPrimitive("Transparent Sphere 3", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, 3.5, -3),
                                                      glm::vec3(0, 0, 0),
                                                      glm::vec3(3, 3, 3)),
             Color3f(0,0,0), Color3f(1,1,1));

    //mirrored_specular2
    addPrimitive("Reflective Sphere Blue2", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(0.25,0.5,1));

    //yellow_diffuse
    addPrimitive("Yellow Sphere", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(0, 0, 0),
                                                    glm::vec3(0, 0, 0),
                                                    glm::vec3(2, 2, 2)),
                 Color3f(0,0,0), Color3f(1, 1, 0.25));

}

void Scene::setSceneRefl(){
    Point3f eye(0, 0.5, 12);
    Vector3f ref(0, 0, 0);
    Vector3f worldUp(0, 1, 0);
    float fov = 50.0;
    float width = 400;
    float height = 400;
    setCamera(eye, ref, worldUp, fov, width, height);

    //point light1
    addPrimitive("point light1", ShapeType::noneShape, LightType::pointlight,
                 MaterialType::noneMaterial, Transform(glm::vec3(0, 4, 5),
                                           glm::vec3(0, 0, 0),
                                           glm::vec3(0.5, 0.5, 0.5)),
                 1.f * Color3f(1,1,1), Color3f(0,0,0));

    //white diffuse
    addPrimitive("Back Wall", ShapeType::squarePlane, LightType::noneLight,
                 MaterialType::lambert ,Transform(glm::vec3(0, 0, -5),
                                               glm::vec3(0, 0, 0),
                                               glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));
    //green diffuse
    addPrimitive("Right Wall", ShapeType::squarePlane, LightType::noneLight,
                 MaterialType::lambert, Transform(glm::vec3(5, 0, 0),
                                               glm::vec3(0, -90, 0),
                                               glm::vec3(10, 10, 1)),
                  Color3f(0,0,0), Color3f(0,1,0));

    // red diffuse
    addPrimitive("Left Wall", ShapeType::squarePlane, LightType::noneLight,
                 MaterialType::lambert, Transform(glm::vec3(-5, 0, 0),
                                                 glm::vec3(0, 90, 0),
                                                 glm::vec3(10,10,1)),
                  Color3f(0,0,0), Color3f(1,0,0));

    //black_diffuse
    addPrimitive("ceiling", ShapeType::squarePlane, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(0, 5, 0),
                                                 glm::vec3(90, 0, 0),
                                                 glm::vec3(10, 10, 1)),
                  Color3f(0,0,0), Color3f(1,1,1));

    //white_diffuse
    addPrimitive("Floor", ShapeType::squarePlane, LightType::noneLight,
                 MaterialType::lambert, Transform(glm::vec3(0, -5, 0),
                                                glm::vec3(-90, 0, 0),
                                                glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //purple_specular
    addPrimitive("Shiny Sphere", ShapeType::sphere, LightType::noneLight,
                 MaterialType::blinn, Transform(glm::vec3(-2, -5, 0),
                                                             glm::vec3(0, 0, 0),
                                                             glm::vec3(5, 5, 5)),
                 Color3f(0,0,0), Color3f(0.75, 0.0, 0.75));

    //refractive_specular
    addPrimitive("Transparent Sphere 1", ShapeType::sphere, LightType::noneLight,
                 MaterialType::specTrans, Transform(glm::vec3(-3, 0, 2),
                                                             glm::vec3(0, 0, 0),
                                                             glm::vec3(4, 4, 4)),
                 Color3f(0,0,0), Color3f(1,1,1), 1.33, 1);

    //air_bubble_mat
    addPrimitive("Inside Transparent Sphere 1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::specTrans, Transform(glm::vec3(-3, 0, 2),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(2.5, 2.5, 2.5)),
                 Color3f(0,0,0), Color3f(1,1,1), 1, 1.33);

    //refractive_specular2
    addPrimitive("Transparent Sphere Green", ShapeType::sphere, LightType::noneLight,
                  MaterialType::specTrans, Transform(glm::vec3(3, -2, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(4, 4, 4)),
                 Color3f(0,0,0), Color3f(0.15, 1, 0.15), 1.33, 1);

    //white_diffuse
    addPrimitive("Inside Opaque 1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(3, -2, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(1,1,1));

    //mirrored_specular2
    addPrimitive("Reflective Sphere Blue1", ShapeType::sphere, LightType::noneLight,
                  MaterialType::specRefl, Transform(glm::vec3(-3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(3, 3, 3)),
                 Color3f(0,0,0), Color3f(0.25,0.5,1));

    //refractive_specular
    addPrimitive("Transparent Sphere 3", ShapeType::sphere, LightType::noneLight,
                  MaterialType::specTrans, Transform(glm::vec3(3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(3, 3, 3)),
                 Color3f(0,0,0), Color3f(1,1,1), 1.33, 1);

    //mirrored_specular2
    addPrimitive("Reflective Sphere Blue2", ShapeType::sphere, LightType::noneLight,
                  MaterialType::specRefl, Transform(glm::vec3(3, 3.5, -3),
                                                              glm::vec3(0, 0, 0),
                                                              glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(0.25,0.5,1));

    //yellow_diffuse
    addPrimitive("Yellow Sphere", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(0, 0, 0),
                                                    glm::vec3(0, 0, 0),
                                                    glm::vec3(2, 2, 2)),
                 Color3f(0,0,0), Color3f(1, 1, 0.25));

}

void Scene::setSceneAreaLight() {

    Point3f eye(5, 5, 5);
    Vector3f ref(0, 2, 0);
    Vector3f worldUp(0, 1, 0);
    float fov = 50.0;
    float width = 400;
    float height = 400;
    setCamera(eye, ref, worldUp, fov, width, height);

    // area light
    addLightPrimitive("Area Light", ShapeType::squarePlane, LightType::areaLight,
                      Transform(glm::vec3(0, 3.5, 0),
                                  glm::vec3(90, 0, 0),
                                  glm::vec3(2, 2, 1)),
                      Color3f(1,1,1), 256, STRATIFIED, DISC_UNIFORM);

    //sphere
    addPrimitive("Sphere", ShapeType::sphere, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(0, 1, 0),
                                                    glm::vec3(0, 0, 0),
                                                    glm::vec3(1, 1, 1)),
                 Color3f(0,0,0), Color3f(1, 1, 1));

    // floor plane
    addPrimitive("Floor Plane", ShapeType::squarePlane, LightType::noneLight,
                  MaterialType::lambert, Transform(glm::vec3(0, 0, 0),
                                                    glm::vec3(-90, 0, 0),
                                                    glm::vec3(10, 10, 1)),
                 Color3f(0,0,0), Color3f(1, 1, 1));
}

bool Scene::getIntersection(const Ray& ray, Intersection *intersect, int testShadow) const {
    float nearest_t = 10000;
    int primiSize = m_primitives.size();
    bool isHit = false;
    glm::vec3 tmp_normal;
    int primitiveHitNum = -1;

    for (int i = 0; i < primiSize; i++) {

        if (nullptr == m_primitives[i]->material && nullptr == m_primitives[i]->shape) {
            continue;
        }
        if (nullptr != m_primitives[i]->material) {
            if(testShadow == 1 && m_primitives[i]->material->materialType == MaterialType::specTrans) {
                continue;
            }

            if (testShadow == 2 && m_primitives[i]->material->materialType != MaterialType::specTrans) {
                continue;
            }
        }

        Intersection tmp_intersect;
        Ray tmpRay = ray;
        Ray transRay = tmpRay.transformRay(m_primitives[i]->shape->transform.WorldTransformInverse);
        if (m_primitives[i]->getIntersection(transRay, &tmp_intersect)){
            if (tmp_intersect.t < nearest_t && tmp_intersect.t > 0.00001) {
                nearest_t = tmp_intersect.t;
                tmp_normal = tmp_intersect.normal;
                isHit = true;
                primitiveHitNum = i;
            }
        }
    }
    if (isHit) {
        intersect->normal = tmp_normal;
        intersect->t = nearest_t;
        intersect->point = ray.origin + nearest_t * ray.direction;
        intersect->objectHit = m_primitives[primitiveHitNum].get();
    }
    return isHit;
}
