#pragma once

#include <QMainWindow>

#include "ui/resources/ui_main_window.h"
#include "ui/graphics_scene.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow ui;
    GraphicsScene* scene;
};
