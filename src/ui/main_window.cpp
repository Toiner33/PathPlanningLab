#include <QMessageBox>

#include "ui/main_window.hpp"
#include "ui/graphics_scene.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) 
{
    ui.setupUi(this);

    // Connect events
    QObject::connect(ui.runAlgorithmBt, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Path Planning", "Running algorithm!");
    });


    QObject::connect(ui.drivableBt, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Drawing mode", "Drawing drivable area!");
    });

    scene = new GraphicsScene(this);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(0, 0, 500, 500);
    scene->drawGrid(25, 25, 20);
}

MainWindow::~MainWindow() {}