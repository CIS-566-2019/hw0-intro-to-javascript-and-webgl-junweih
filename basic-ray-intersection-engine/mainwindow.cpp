#include "mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->save_Image_pushButton, SIGNAL(clicked(bool)),
            this, SLOT(slot_saveImage()));

//    rendered_image = renderSphereScene(scene.camera);
//    rendered_image = renderSquarePlaneScene(scene.camera);
//    rendered_image = renderScene1(scene.camera);
//    rendered_image = renderScene2(scene.camera);
//    rendered_image = renderRayCastScene(scene.camera);
//    rendered_image = renderLambert();
//    rendered_image = renderRefl();
//    rendered_image = renderShadow();
//    rendered_image = renderTwoLight();
//    rendered_image = renderAreaLight();
    rendered_image = renderAmbientOcclusion();

//    rendered_image = renderAmbientCombine();
    DisplayQImage(rendered_image);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayQImage(QImage &i)
{
    QPixmap pixmap(QPixmap::fromImage(i));
    graphics_scene.addPixmap(pixmap);
    graphics_scene.setSceneRect(pixmap.rect());
    ui->scene_display->setScene(&graphics_scene);
}
void MainWindow::slot_saveImage() {
    QString imagePath = QFileDialog::getSaveFileName(
                       this,
                        tr("Save File"),
                        "../",
                        tr("PNG (*.png)" ));
    rendered_image.save(imagePath);
}
QImage MainWindow::renderRayCastScene(Camera cam) {
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image (width, height, QImage::Format_RGB32);
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++) {
            Ray outRay = cam.rayCast(glm::vec2(x, y));
            glm::vec3 rgb = 255.f * (outRay.direction + glm::vec3(1, 1, 1)) * 0.5f;
            QColor color = qRgb(rgb.x, rgb.y, rgb.z);
            image.setPixelColor(x, y, color);
        }
    }
    return image;
}

QImage MainWindow::renderScene1(Camera cam) {
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image (width, height, QImage::Format_RGB32);
    scene.setScene1();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray outRay = cam.rayCast(glm::vec2(x, y));
            Intersection* intersect = new Intersection();
            glm::vec3 rgb(0,0,0);
            if (scene.getIntersection(outRay, intersect)) {
                rgb = 255.f * (intersect->normal + glm::vec3(1, 1, 1)) * 0.5f;
            }
            QColor color = qRgb(rgb.x, rgb.y, rgb.z);
            image.setPixelColor(x, y, color);

        }
    }
    return image;
}

QImage MainWindow::renderScene2(Camera cam) {
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image (width, height, QImage::Format_RGB32);
    scene.setScene2();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray outRay = cam.rayCast(glm::vec2(x, y));
            Intersection* intersect = new Intersection();
            glm::vec3 rgb(0,0,0);
            if (scene.getIntersection(outRay, intersect)) {
                rgb = 255.f * (intersect->normal + glm::vec3(1, 1, 1)) * 0.5f;
            }
            QColor color = qRgb(rgb.x, rgb.y, rgb.z);
            image.setPixelColor(x, y, color);

        }
    }
    return image;
}





QImage MainWindow::renderSphereScene(Camera cam) {
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image (width, height, QImage::Format_RGB32);
    Sphere sphere = Sphere();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray ray = cam.rayCast(glm::vec2(x, y));
            Ray outRay = ray.transformRay(sphere.transform.WorldTransformInverse);
            Intersection* intersect = new Intersection();
            glm::vec3 rgb = glm::vec3(0,0,0);
            if (sphere.getIntersection(outRay, intersect)) {
                rgb = 255.f * (intersect->normal + glm::vec3(1, 1, 1)) * 0.5f;
            }
            QColor color = qRgb(rgb.x, rgb.y, rgb.z);
            image.setPixelColor(x, y, color);
        }
    }
    return image;
}

QImage MainWindow::renderSquarePlaneScene(Camera cam) {
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image (width, height, QImage::Format_RGB32);
    SquarePlane sphere;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray outRay = cam.rayCast(glm::vec2(x, y));
            Intersection* intersect = new Intersection();
            glm::vec3 rgb = glm::vec3(0,0,0);
            if (sphere.getIntersection(outRay, intersect)) {
                rgb = 255.f * (intersect->normal + glm::vec3(1, 1, 1)) * 0.5f;
            }
            QColor color = qRgb(rgb.x, rgb.y, rgb.z);
            image.setPixelColor(x, y, color);
        }
    }
    return image;
}


QImage MainWindow::renderShadow() {
//    scene.setSceneLambert();
    scene.setSceneTwoLights();
    Camera cam = scene.camera;
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image(width, height, QImage::Format_RGB32);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray currentRay = cam.rayCast(glm::vec2(x, y));
            Intersection *intersect = new Intersection();
            glm::vec3 rgb(0,0,0);

            if (scene.getIntersection(currentRay, intersect)) {
                for (unsigned int i = 0; i < scene.m_primitives.size(); i++) {
                    if (nullptr == scene.m_primitives[i]->light){
                        break;
                    }
//                    if (scene.m_primitives[i]->light->inShadow(*intersect, scene)) {
//                        rgb = 255.f * Color3f(1);
//                    }
                }
            }
            else {
                rgb = Color3f(0,0,0);
            }
            QColor color = qRgb(rgb.r, rgb.g, rgb.b);

            image.setPixelColor(x, y, color);
        }
    }
    return image;
}

QImage MainWindow::renderLambert() {
    scene.setSceneLambert();
    QImage image = renderEngine();
    return image;
}

QImage MainWindow::renderRefl() {
    scene.setSceneRefl();
    QImage image = renderEngine();
    return image;
}

QImage MainWindow::renderTwoLight() {
    scene.setSceneTwoLights();

    QImage image = renderEngine();
    return image;
}

QImage MainWindow::renderAreaLight() {

    scene.setSceneAreaLight();
    QImage image = renderEngine();

    return image;
}

QImage MainWindow::renderAmbientOcclusion() {
    scene.setSceneLambert();
    QImage image = renderAmbientEngine();

//    QImage image = renderEngine();
    return image;
}


QImage MainWindow::renderAmbientCombine() {
    scene.setSceneLambert();
    QImage image1 = renderEngine();
    QImage image2 = renderAmbientEngine();
    QImage image = combineTwoImage(image1, image2);
    return image;
}

QImage MainWindow::combineTwoImage(QImage image1, QImage image2) {
    int width = image1.width();
    int height = image1.height();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
//            QColor pi
        }
    }
}


QImage MainWindow::renderEngine() {
    Camera cam = scene.camera;
    int width = floor(cam.width);
    int height = floor(cam.height);
    QImage image(width, height, QImage::Format_RGB32);
    scene.iterMax = 5;
//    for (int x = 39 ; x < width; x++) {
//        for (int y = 321; y < height; y++) {


    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray outRay = cam.rayCast(glm::vec2(x,y));
            Intersection *intersect = new Intersection();
            Ray currentRay = outRay;
            glm::vec3 rgb(0,0,0);
            scene.iterTimes = 0;
            bool hitAreaLight = false;
            if (scene.getIntersection(outRay, intersect)) {
                if (nullptr != intersect->objectHit->light) {
                    if (intersect->objectHit->light->lightType == LightType::areaLight) {
                        rgb = intersect->objectHit->light->color;
                        hitAreaLight = true;
                    }
                }
                if(!hitAreaLight) {
                    for (unsigned int i = 0; i < scene.m_primitives.size(); i++) {
                        if (nullptr == scene.m_primitives[i]->light) {
                            continue;
                        }
                        Color3f tmpColor = intersect->objectHit->material->getScatteredColor(*intersect, currentRay, scene);
                        rgb = glm::clamp(rgb + tmpColor, Color3f(0,0,0), Color3f(1,1,1));
    //                    std::cout << rgb.x << " " << rgb.y << " " << rgb.z << std::endl;
                    }
                }
            }
            rgb = 255.f * rgb;
            QColor color = qRgb(rgb.r, rgb.g, rgb.b);
            image.setPixelColor(x, y, color);
        }
    }
    return image;
}

inline void CoordinateSystem(const Vector3f& v1, Vector3f* v2, Vector3f* v3)
{
    if (std::abs(v1.x) > std::abs(v1.y))
            *v2 = Vector3f(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
        else
            *v2 = Vector3f(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
        *v3 = glm::cross(v1, *v2);
}

QImage MainWindow::renderAmbientEngine() {
    Camera cam = scene.camera;
    int width = floor(cam.width);
    int height = floor (cam.height);
    QImage image(width, height, QImage::Format_RGB32);

    std::vector<Point3f> m_samplePoints = MainWindow::generateSample(10 * 10, GRID, HEMISPHERE_UNIFORM);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Ray outRay = cam.rayCast(glm::vec2(x, y));
            Intersection *intersect = new Intersection();
            Color3f rgb(0,0,0);
            if (scene.getIntersection(outRay, intersect)) {
                Point3f point = intersect->point;
                Normal3f normal = intersect->normal;
                Vector3f tangent;
                Vector3f bitangent;
                CoordinateSystem(normal, &tangent, &bitangent);
                glm::mat3 transMat (tangent, bitangent, normal);
                for (int i = 0; i < m_samplePoints.size(); i++) {
                    Vector3f unTransSample2Point = glm::normalize(m_samplePoints[i]);
                    Vector3f rayDir = transMat * unTransSample2Point;
                    Ray sampleRay (point + 0.0001f * normal, glm::normalize(rayDir));
                    float epsilon = 0.5;
                    rgb = rgb + ambientShadowTest(sampleRay, scene, epsilon);
                }
//                std::cout << totalDir.x << " " << totalDir.y << " " << totalDir.z  << std::endl;
            }
            rgb = rgb / float(m_samplePoints.size());
            rgb = 255.f * rgb;
            QColor color = qRgb(rgb.r, rgb.g, rgb.b);
            image.setPixelColor(x, y, color);
        }
    }
    return image;
}


Color3f MainWindow::ambientShadowTest(const Ray &ray, const Scene &scene, float epsilon) {
    Intersection* tmpIntersect = new Intersection();
    // intersect only with opaque primitive
    float tLight2Point = -1;
    if (scene.getIntersection(ray, tmpIntersect, 0)) {
        tLight2Point = tmpIntersect->t;
        if (tLight2Point < epsilon && tLight2Point > 0) {
            return Color3f(0,0,0);
        }
    }
    return Color3f(1,1,1);
}

std::vector<Point3f> MainWindow::generateSample(int numSamples, SampleMode sampleMode,
                                WarpMethod warpMethod)
{
    Sampler sampler;
    std::vector<Point3f> m_samplePoints;
    sampler.generateSamples(numSamples, sampleMode, warpMethod);
    std::vector<float> m_samples = sampler.peekSamples();
    for (int i = 0; i < m_samples.size(); i = i+3) {
        Point3f newPoint(m_samples[i], m_samples[i+1], m_samples[i+2]);
        m_samplePoints.push_back(newPoint);
    }
    return m_samplePoints;
}
