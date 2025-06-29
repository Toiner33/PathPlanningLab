#pragma once

#include <memory>

#include <QMainWindow>

#include "ui/resources/ui_main_window.h"
#include "ui/graphics_scene.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartDrawing();
    void onPointClicked(QPointF point);
    void onDoubleClick(QPointF point);
    void onCursorMoved(QPointF point);

private:
    Ui::MainWindow ui;
    GraphicsScene* scene;

    QVector<QPointF> currentPolygonPoints;
    std::unique_ptr<QGraphicsPolygonItem> previewPolygon;
    QPointF hoverPos;
    bool hovering = false;

    void updatePreview();
    void finalizePolygon();
    void resetDrawingState();

    inline static const QColor PreviewGreen = QColor(136, 247, 146, 128);
    inline static const QColor FinalGreen = QColor(136, 247, 146, 255);
};
