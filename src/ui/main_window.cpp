#include <QMessageBox>

#include "ui/main_window.hpp"
#include "ui/graphics_scene.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(std::make_shared<GraphicsScene>(this)),
    drivablePolygon(scene)
{
    ui.setupUi(this);
    ui.graphicsView->setScene(scene.get());

    QObject::connect(ui.runAlgorithmBt, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Path Planning", "Running algorithm!");
    });

    QObject::connect(ui.drivableBt, &QPushButton::clicked, this, &MainWindow::onStartDrawing);
    QObject::connect(scene.get(), &GraphicsScene::pointClicked, this, &MainWindow::onPointClicked);
    QObject::connect(scene.get(), &GraphicsScene::sceneDoubleClicked, this, &MainWindow::onDoubleClick);
    QObject::connect(scene.get(), &GraphicsScene::cursorMoved, this, &MainWindow::onCursorMoved);

    ui.graphicsView->setRenderHint(QPainter::Antialiasing);
    ui.graphicsView->setMouseTracking(true);
    scene->setSceneRect(0, 0, 500, 500);

    // scene->drawGrid(25, 25, 20);
}

MainWindow::~MainWindow() {}

void MainWindow::onStartDrawing() {
    if (!currentPolygon) {
        currentPolygon = std::make_shared<utils::geometry::SmartPolygon>(
            utils::visuals::colors::drivableGreen);
    }

    drivablePolygon.addPolygon(currentPolygon);
    scene->setDrawingEnabled(true);
}

void MainWindow::onPointClicked(QPointF point) {
    currentPolygon->addPoint(point);
}

void MainWindow::onDoubleClick(QPointF point) {
    currentPolygon->addPoint(point);

    if (!currentPolygon->finalizePolygon()) {
        drivablePolygon.popPolygon();
    }

    currentPolygon.reset();
    scene->setDrawingEnabled(false);
}

void MainWindow::onCursorMoved(QPointF point) {
    currentPolygon->setPreview(point);
}