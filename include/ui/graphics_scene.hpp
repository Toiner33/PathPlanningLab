#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QHashFunctions>
#include <QPointF>
#include <QKeyEvent>

#include <unordered_map>
#include <array>

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    // void drawGrid(int rows, int cols, int cellSize);
    void setDrawingEnabled(bool enabled);
        
signals:
    void sceneClicked(const QPointF& scenePos);
    void pointClicked(const QPointF& scenePos);
    void sceneDoubleClicked(const QPointF& scenePos);
    void cursorMoved(const QPointF& scenePos);
    void stopDrawing();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    // int cellResolution;
    // std::array<int, 2> gridSize;
    // std::unordered_map<int, QGraphicsRectItem*> cellMap;
    bool drawingEnabled = false;
};