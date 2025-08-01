#include <iostream>

#include <QMessageBox>

#include "ui/main_window.hpp"
#include "ui/graphics_scene.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(std::make_shared<GraphicsScene>(this)),
    drivablePolygon(scene)
{
    ui.setupUi(this);
    scene->setSceneRect(-5000, -5000, 10000, 10000);
    ui.graphicsView->setScene(scene.get());

    // Drawing buttons
    QObject::connect(ui.stopDrawingBt, &QPushButton::clicked, this, &MainWindow::onStopDrawing);
    QObject::connect(ui.sceneClearBt, &QPushButton::clicked, this, &MainWindow::clearAllPolygons);
    
    // Drawing Tools Box Signals
    QObject::connect(ui.eraseBt, &QPushButton::toggled, this,
        [this](bool checked){ this->tryDrawingModeBt(checked, DrawingMode::REMOVE, ui.eraseBt); }
    );
    QObject::connect(ui.drawBt, &QPushButton::toggled, this,
        [this](bool checked){ this->tryDrawingModeBt(checked, DrawingMode::ADD, ui.drawBt); }
    );

    // Drawing Area Box Signals
    QObject::connect(ui.drivableBt, &QPushButton::toggled, this,
        [this](bool checked){ this->tryDrawingAreaBt(checked, DrawingArea::DRIVABLE, ui.drivableBt); }
    );

    // Scene signals
    QObject::connect(scene.get(), &GraphicsScene::pointClicked, this, &MainWindow::onPointClicked);
    QObject::connect(scene.get(), &GraphicsScene::sceneClicked, this, &MainWindow::onSceneClicked);
    QObject::connect(scene.get(), &GraphicsScene::sceneDoubleClicked, this, &MainWindow::onDoubleClick);
    QObject::connect(scene.get(), &GraphicsScene::cursorMoved, this, &MainWindow::onCursorMoved);
    QObject::connect(scene.get(), &GraphicsScene::stopDrawing, this, &MainWindow::onStopDrawing);
    QObject::connect(scene.get(), &GraphicsScene::zoomInOut, this, &MainWindow::onZoomInOut);

    // scene->drawGrid(25, 25, 20);
}

MainWindow::~MainWindow() {}

void MainWindow::onZoomInOut(double factor) { 
    ui.graphicsView->scale(factor, factor);
}

void MainWindow::tryDrawingModeBt(bool checked, const DrawingMode& mode, QPushButton* button) {
    const DrawingMode& finalMode = checked ? mode : DrawingMode::NONE;
    if (!setDrawingMode(finalMode)) {
        forceButtonState(button, !checked); // Reject state change
        return;
    }

    if (currentToolButton != button) {
        forceButtonState(currentToolButton, false);
        currentToolButton = button;
    }

    setCorrectInteractionMode();
}

void MainWindow::tryDrawingAreaBt(bool checked, const DrawingArea& area, QPushButton* button) {
    const DrawingArea& finalArea = checked ? area : DrawingArea::NONE;
    if (!setDrawingArea(finalArea)) {
        forceButtonState(button, !checked); // Reject state change
    }

    if (currentAreaButton != button) {
        forceButtonState(currentAreaButton, false);
        currentAreaButton = button;
    }

    setCorrectInteractionMode();
}

void MainWindow::forceButtonState(QPushButton* button, bool state) {
    if (!button) { return; }
    button->blockSignals(true);
    button->setChecked(state);
    button->blockSignals(false);
}

void MainWindow::onStopDrawing() {
    if (currentPolygon && activeArea()->back() == currentPolygon) {
        activeArea()->popPolygon();
    }

    currentPolygon.reset();
    scene->setDrawingEnabled(false);
    drawingArea = DrawingArea::NONE;
    drawingMode = DrawingMode::NONE;
    forceButtonState(ui.drawBt, false);
    forceButtonState(ui.eraseBt, false);
    forceButtonState(ui.drivableBt, false);
    currentToolButton = nullptr;
    currentAreaButton = nullptr;
    setCorrectInteractionMode();
}

void MainWindow::setCorrectInteractionMode() {
    if (isDrawing()) {
        ui.graphicsView->setCursor(Qt::CrossCursor);
        ui.graphicsView->setDragMode(QGraphicsView::NoDrag);
    } else {
        ui.graphicsView->setCursor(Qt::SizeAllCursor);
        ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void MainWindow::clearAllPolygons() {
    onStopDrawing();
    drivablePolygon.clear();
}

bool MainWindow::setDrawingMode(const DrawingMode& mode) {
    if (currentPolygon) {
        QMessageBox::warning(nullptr, "Drawing Settings", "Please stop drawing before changing modes");
        return false;
    }

    drawingMode = mode;
    return true;
}
bool MainWindow::setDrawingArea(const DrawingArea& area) {
    if (currentPolygon) {
        QMessageBox::warning(nullptr, "Drawing Settings", "Please stop drawing before changing areas");
        return false;
    }

    drawingArea = area;
    return true;
}

bool MainWindow::isDrawing(){
    return drawingMode != DrawingMode::NONE && drawingArea != DrawingArea::NONE;
}

void MainWindow::onSceneClicked(const QPointF& scenePos) {
    if (!isDrawing()) {
        return;
    }

    onStartDrawing();
    onPointClicked(scenePos);
}

void MainWindow::onStartDrawing() {    
    if (drawingArea == DrawingArea::NONE || drawingMode == DrawingMode::NONE) {
        QMessageBox::warning(nullptr, "Drawing Settings", "Incorrect drawing settings!");
        return;
    }

    addCurrent();
    scene->setDrawingEnabled(true);
}

void MainWindow::onPointClicked(const QPointF& point) {
    currentPolygon->addPoint(point);
}

void MainWindow::onDoubleClick(const QPointF& point) {
    currentPolygon->addPoint(point);

    if (!currentPolygon->finalizePolygon()) {
        removeCurrent();
    }

    applyCurrent();

    currentPolygon.reset();
    scene->setDrawingEnabled(false);
}

void MainWindow::onCursorMoved(const QPointF& point) {
    currentPolygon->setPreview(point);
}

utils::geometry::SmartMultiPolygon* MainWindow::activeArea() {
    switch (drawingArea) {
        case DrawingArea::DRIVABLE:
            return &drivablePolygon;
        case DrawingArea::NONE:
            QMessageBox::warning(nullptr, "Area Selection", "No area has been selected!");
            return nullptr;
        default:
            QMessageBox::warning(nullptr, "Area Selection", "An unknown area has been selected!");
            return nullptr;
    }
}

void MainWindow::addCurrent() {
    if (!currentPolygon) {
        currentPolygon = 
            std::make_shared<utils::geometry::SmartPolygon>(getColor(drawingMode, drawingArea));
    }
    
    switch (drawingMode) {
        case DrawingMode::ADD:
            activeArea()->addPolygon(currentPolygon);
            break;
        case DrawingMode::REMOVE:
            scene->addItem(currentPolygon.get());
            break;
        default:
            std::cout << "Unknown drawing mode while adding current polygon. " << std::endl;
            break;
    }
}

void MainWindow::removeCurrent() {
    switch (drawingMode) {
        case DrawingMode::ADD:
            activeArea()->popPolygon();
            break;
        case DrawingMode::REMOVE:
            scene->removeItem(currentPolygon.get());
            break;
        default:
            std::cout << "Unknown drawing mode removing current polygon. " << std::endl;
            break;
    }
}

void MainWindow::applyCurrent() {
    switch (drawingMode) {
        case DrawingMode::ADD:
            activeArea()->mergeOverlapping();
            break;
        case DrawingMode::REMOVE:
            activeArea()->eraseOverlapping(*currentPolygon);
            break;
        default:
            std::cout << "Unknown drawing mode while applying current polygon. " << std::endl;
            break;
    }
}


QColor MainWindow::getColor(
    const DrawingMode& mode,
    const DrawingArea& area
){
    if (mode == DrawingMode::NONE || area == DrawingArea::NONE) {
        return QColor();
    } else if (mode == DrawingMode::REMOVE) {
        return utils::visuals::colors::eraserColor;
    } else {
        return areaColorsMap.at(area);
    }
}