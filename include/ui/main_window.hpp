#pragma once

#include <memory>
#include <optional>
#include <vector>

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

private slots:
    void onStartDrawing();
    void onPointClicked(QPointF point);
    void onDoubleClick(QPointF point);
    void onCursorMoved(QPointF point);

private:
    Ui::MainWindow ui;
    std::shared_ptr<GraphicsScene> scene;
    
    utils::geometry::SmartPolygon::SharedPtr currentPolygon;
    utils::geometry::SmartMultiPolygon drivablePolygon;
};
