#include <iostream>

#include <QBrush>
#include <QGraphicsSceneMouseEvent>

#include "ui/graphics_scene.hpp"

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent) {}

void GraphicsScene::setDrawingEnabled(bool enabled) {
    drawingEnabled = enabled;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {    
    if (event->button() == Qt::LeftButton) {
        emit drawingEnabled ? 
            pointClicked(event->scenePos()) :
            sceneClicked(event->scenePos());
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    if (drawingEnabled && event->button() == Qt::LeftButton) {
        emit sceneDoubleClicked(event->scenePos());
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (drawingEnabled) {
        emit cursorMoved(event->scenePos());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        emit stopDrawing();
    }
    QGraphicsScene::keyPressEvent(event);
}

// void GraphicsScene::drawGrid(int rows, int cols, int size) {
//     cellResolution = size;
//     gridSize = {rows, cols};
//     for (int row = 0; row < rows; ++row) {
//         for (int col = 0; col < cols; ++col) {
//             QGraphicsRectItem* rect = addRect(
//                 col * cellResolution,
//                 row * cellResolution,
//                 cellResolution,
//                 cellResolution
//             );
            
//             if (col == 0 || col == cols - 1 || row == 0 || row == rows - 1) {
//                 rect->setBrush(Qt::black);
//             } else {
//                 rect->setBrush(Qt::white);
//             }
//             rect->setPen(QPen(Qt::gray));
//             cellMap[row * gridSize[1] + col] = rect;
//         }
//     }
// }

// void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
//     QPointF clickPos = event->scenePos();
//     int col = clickPos.x() / cellResolution;
//     int row = clickPos.y() / cellResolution;
//     int cellIndx = row * gridSize[1] + col;

//     if (cellMap.find(cellIndx) != cellMap.end()) {
//         QGraphicsRectItem* rect = cellMap[cellIndx];
//         QColor current = rect->brush().color();
//         rect->setBrush(current == Qt::black ? 
//             col == 0 || col == gridSize[1] - 1 || row == 0 || row == gridSize[0] - 1 ? Qt::black : Qt::white :
//             Qt::black
//         );
//     }
// }