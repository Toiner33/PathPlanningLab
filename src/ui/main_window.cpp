#include <QMessageBox>

#include "ui/main_window.hpp"
#include "ui/graphics_scene.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) 
{
    ui.setupUi(this);

    // Connect events
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Path Planning", "Running algorithm!");
    });

    scene = new GraphicsScene(this);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(0, 0, 500, 500);
    scene->drawGrid(25, 25, 20);
}

MainWindow::~MainWindow() {}