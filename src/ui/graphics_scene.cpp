#include <iostream>

#include <QBrush>
#include <QGraphicsSceneMouseEvent>

#include "ui/graphics_scene.hpp"

namespace ui {

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

void GraphicsScene::drawBackground(QPainter* painter, const QRectF& rect) {
    painter->setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    qreal left = std::floor(rect.left() / backgroundGridSize) * backgroundGridSize;
    qreal top = std::floor(rect.top() / backgroundGridSize) * backgroundGridSize;

    for (qreal x = left; x < rect.right(); x += backgroundGridSize)
        painter->drawLine(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += backgroundGridSize)
        painter->drawLine(QLineF(rect.left(), y, rect.right(), y));

    // Draw axis
    painter->setPen(QPen(Qt::red, 1, Qt::DotLine));
    painter->drawLine(QLineF(0, rect.top(), 0, rect.bottom())); // Y axis

    painter->setPen(QPen(Qt::blue, 1, Qt::DotLine));
    painter->drawLine(QLineF(rect.left(), 0, rect.right(), 0)); // X axis
}

void GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent* event) {
    emit event->delta() > 0 ? zoomInOut(zoomFactor) : zoomInOut(1 / zoomFactor);
    event->accept();
}

}  // namespace ui