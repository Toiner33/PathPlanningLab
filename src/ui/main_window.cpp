#include <QMessageBox>

#include "ui/main_window.hpp"
#include "ui/graphics_scene.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(std::make_shared<GraphicsScene>(this))
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
    drivablePolygon.emplace_back(
        std::make_shared<utils::geometry::SmartPolygon>(
            utils::visuals::colors::drivableGreen
        )
    );
    scene->setDrawingEnabled(true);
    scene->addItem(drivablePolygon.back().get());
}

void MainWindow::onPointClicked(QPointF point) {
    drivablePolygon.back()->addPoint(point);
}

void MainWindow::onDoubleClick(QPointF point) {
    scene->setDrawingEnabled(false);
    drivablePolygon.back()->addPoint(point);
    if (!drivablePolygon.back()->finalizePolygon()) {
        scene->removeItem(drivablePolygon.back().get());
        drivablePolygon.pop_back();
        return;
    }
}

void MainWindow::onCursorMoved(QPointF point) {
    drivablePolygon.back()->setPreview(point);
}