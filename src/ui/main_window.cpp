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
    ui.graphicsView->setScene(scene.get());

    QObject::connect(ui.runAlgorithmBt, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Path Planning", "Running algorithm!");
    });

    // Drawing Mode Box Signals

    auto tryDrawingMode = [this](
        bool checked,
        const DrawingMode& mode,
        QPushButton* button
    ) {
        if (!setDrawingMode(mode)) {
            forceButtonState(button, !checked);
        }
    };

    auto tryDrawingArea = [this](
        bool checked,
        const DrawingArea& area,
        QPushButton* button
    ) {
        if (!setDrawingArea(area)) {
            forceButtonState(button, !checked);
        }
    };

    QObject::connect(ui.eraseBt, &QPushButton::toggled, this,
        [this, tryDrawingMode](bool checked){ tryDrawingMode(checked, DrawingMode::REMOVE, ui.eraseBt); }
    );
    QObject::connect(ui.drawBt, &QPushButton::toggled, this,
        [this, tryDrawingMode](bool checked){ tryDrawingMode(checked, DrawingMode::ADD, ui.drawBt); }
    );

    // Drivable Area Box Signals
    QObject::connect(ui.drivableBt, &QPushButton::toggled, this,
        [this, tryDrawingArea](bool checked){ tryDrawingArea(checked, DrawingArea::DRIVABLE, ui.drivableBt); }
    );

    // Scene signals
    QObject::connect(scene.get(), &GraphicsScene::pointClicked, this, &MainWindow::onPointClicked);
    QObject::connect(scene.get(), &GraphicsScene::sceneClicked, this, &MainWindow::onSceneClicked);
    QObject::connect(scene.get(), &GraphicsScene::sceneDoubleClicked, this, &MainWindow::onDoubleClick);
    QObject::connect(scene.get(), &GraphicsScene::cursorMoved, this, &MainWindow::onCursorMoved);
    QObject::connect(scene.get(), &GraphicsScene::stopDrawing, this, &MainWindow::onStopDrawing);

    ui.graphicsView->setRenderHint(QPainter::Antialiasing);
    ui.graphicsView->setMouseTracking(true);
    scene->setSceneRect(0, 0, 500, 500);

    // scene->drawGrid(25, 25, 20);
}

MainWindow::~MainWindow() {}

void MainWindow::forceButtonState(QPushButton* button, bool state) {
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
}

bool MainWindow::setDrawingMode(const DrawingMode& mode) {
    if (drawingMode != DrawingMode::NONE) {
        QMessageBox::warning(nullptr, "Drawing Settings", "Please stop drawing before changing modes");
        return false;
    }

    drawingMode = mode;

    return true;
}
bool MainWindow::setDrawingArea(const DrawingArea& area) {
    if (drawingArea != DrawingArea::NONE) {
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
        QMessageBox::warning(nullptr, "Drawing Settings", "Please select drawing tool and area first!");
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

    if (!currentPolygon) {
        currentPolygon = 
            std::make_shared<utils::geometry::SmartPolygon>(getColor(drawingMode, drawingArea));
    }

    if (drawingMode == DrawingMode::ADD) {
        activeArea()->addPolygon(currentPolygon);
    } else if (drawingMode == DrawingMode::REMOVE) {
        scene->addItem(currentPolygon.get());
    }

    scene->setDrawingEnabled(true);
}

void MainWindow::onPointClicked(const QPointF& point) {
    currentPolygon->addPoint(point);
}

void MainWindow::onDoubleClick(const QPointF& point) {
    currentPolygon->addPoint(point);

    if (!currentPolygon->finalizePolygon()) {
        if (drawingMode == DrawingMode::REMOVE) {
            scene->removeItem(currentPolygon.get());
        } else {
            activeArea()->popPolygon();
        }
    }

    if (drawingMode == DrawingMode::REMOVE) {
        activeArea()->eraseOverlapping(*currentPolygon);
    } else {
        activeArea()->mergeOverlapping();
    }

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