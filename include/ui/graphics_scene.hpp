#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QHashFunctions>
#include <QPointF>

#include <unordered_map>
#include <array>

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    // void drawGrid(int rows, int cols, int cellSize);
    void setDrawingEnabled(bool enabled);

signals:
    void pointClicked(QPointF scenePos);
    void sceneDoubleClicked(QPointF scenePos);
    void cursorMoved(QPointF scenePos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    // int cellResolution;
    // std::array<int, 2> gridSize;
    // std::unordered_map<int, QGraphicsRectItem*> cellMap;

    bool drawingEnabled = false;
};