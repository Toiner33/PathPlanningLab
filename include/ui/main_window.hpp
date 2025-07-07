#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include <QMainWindow>

#include "utils/visuals/colors.hpp"
#include "utils/geometry/smart_polygon.hpp"
#include "utils/geometry/smart_multi_polygon.hpp"


#include "ui/resources/ui_main_window.h"
#include "ui/graphics_scene.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum class DrawingMode {
        NONE,
        ADD,
        REMOVE
    };

    enum class DrawingArea {
        NONE,
        DRIVABLE
    };

private slots:
    void onStartDrawing();
    void onPointClicked(const QPointF& point);
    void onSceneClicked(const QPointF& point);
    void onDoubleClick(const QPointF& point);
    void onCursorMoved(const QPointF& point);
    void onStopDrawing();

private:
    Ui::MainWindow ui;
    std::shared_ptr<GraphicsScene> scene;
    
    utils::geometry::SmartPolygon::SharedPtr currentPolygon;
    utils::geometry::SmartMultiPolygon drivablePolygon;

    DrawingMode drawingMode = DrawingMode::NONE;
    DrawingArea drawingArea = DrawingArea::NONE;

    void forceButtonState(QPushButton* button, bool state);

    bool setDrawingMode(const DrawingMode& mode);
    bool setDrawingArea(const DrawingArea& area);
    bool isDrawing();

    utils::geometry::SmartMultiPolygon* activeArea();

    static inline const std::unordered_map<DrawingArea, QColor> areaColorsMap = {
        {DrawingArea::NONE, QColor()},
        {DrawingArea::DRIVABLE, utils::visuals::colors::drivableGreen}
    };

    static QColor getColor(const DrawingMode& mode, const DrawingArea& area);
};
