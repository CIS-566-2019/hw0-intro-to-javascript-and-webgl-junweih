#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include "camera.h"
#include "scene.h"
#include "QBuffer"
#include "QFileDialog"
#include "ui_mainwindow.h"
#include "iostream"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DisplayQImage(QImage &i);
    QImage renderRayCastScene(Camera cam);
    QImage renderScene1(Camera cam);
    QImage renderScene2(Camera cam);
    QImage renderLambert();
    QImage renderRefl();
    QImage renderShadow();
    QImage renderTwoLight();
    QImage renderAreaLight();
    QImage renderAmbientOcclusion();
    QImage renderAmbientCombine();
    QImage renderEngine();
    QImage renderAmbientEngine();
    QImage combineTwoImage(QImage image1, QImage image2);
    std::vector<Point3f> generateSample(int numSamples, SampleMode sampleMode, WarpMethod warpMethod);
    Color3f ambientShadowTest (const Ray& ray, const Scene& scene, float t);


    QImage renderSphereScene(Camera cam);
    QImage renderSquarePlaneScene(Camera cam);

private:
    Ui::MainWindow *ui;
    //This is used to display the QImage produced by RenderScene in the GUI
    QGraphicsScene graphics_scene;

    //This is the image rendered by your program when it loads a scene
    QImage rendered_image;


    Scene scene;

public slots:
    void slot_saveImage();
};

#endif // MAINWINDOW_H
