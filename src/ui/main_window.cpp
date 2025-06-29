#include <QMessageBox>

#include "ui/main_window.hpp"
#include "ui/graphics_scene.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new GraphicsScene(this))
{
    ui.setupUi(this);
    ui.graphicsView->setScene(scene);

    QObject::connect(ui.runAlgorithmBt, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Path Planning", "Running algorithm!");
    });

    QObject::connect(ui.drivableBt, &QPushButton::clicked, this, &MainWindow::onStartDrawing);
    QObject::connect(scene, &GraphicsScene::pointClicked, this, &MainWindow::onPointClicked);
    QObject::connect(scene, &GraphicsScene::sceneDoubleClicked, this, &MainWindow::onDoubleClick);
    QObject::connect(scene, &GraphicsScene::cursorMoved, this, &MainWindow::onCursorMoved);

    ui.graphicsView->setRenderHint(QPainter::Antialiasing);
    ui.graphicsView->setMouseTracking(true);
    scene->setSceneRect(0, 0, 500, 500);
    // scene->drawGrid(25, 25, 20);
}

MainWindow::~MainWindow() {}

void MainWindow::onStartDrawing() {
    resetDrawingState();
    scene->setDrawingEnabled(true);
}

void MainWindow::onPointClicked(QPointF point) {
    currentPolygonPoints.append(point);
    updatePreview();
}

void MainWindow::onDoubleClick(QPointF point) {
    currentPolygonPoints.append(point);
    finalizePolygon();
}

void MainWindow::onCursorMoved(QPointF point) {
    hoverPos = point;
    hovering = true;
    updatePreview();
}

void MainWindow::updatePreview() {
    if (!previewPolygon) {
        previewPolygon = std::make_unique<QGraphicsPolygonItem>();
        previewPolygon->setPen(QPen(Qt::black, 1, Qt::DashLine));
        previewPolygon->setBrush(QBrush(PreviewGreen));
        scene->addItem(previewPolygon.get());
    }

    QPolygonF polygon(currentPolygonPoints);
    if (hovering) {
        polygon.append(hoverPos);
    }

    previewPolygon->setPolygon(polygon);
}

void MainWindow::finalizePolygon() {
    if (currentPolygonPoints.size() < 3) {
        QMessageBox::warning(nullptr, "Polygon Drawing", "Polygon must have at least 3 points!");
        resetDrawingState();
        return;
    }

    QPolygonF polygon(currentPolygonPoints);
    std::unique_ptr<QGraphicsPolygonItem> polyItem = std::make_unique<QGraphicsPolygonItem>(polygon);
    polyItem->setBrush(QBrush(FinalGreen));
    polyItem->setPen(QPen(Qt::black));
    scene->addItem(polyItem.get());
    
    resetDrawingState();
}

void MainWindow::resetDrawingState() {
    currentPolygonPoints.clear();
    hovering = false;
    hoverPos = QPointF();

    if (previewPolygon) {
        scene->removeItem(previewPolygon.get());
        previewPolygon.reset();
    }

    scene->setDrawingEnabled(false);
}