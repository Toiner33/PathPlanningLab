#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QHashFunctions>

#include <unordered_map>
#include <array>

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    void drawGrid(int rows, int cols, int cellSize);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int cellResolution;
    std::array<int, 2> gridSize;
    std::unordered_map<int, QGraphicsRectItem*> cellMap;
};