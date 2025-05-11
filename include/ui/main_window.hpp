#pragma once

#include <QMainWindow>

#include "ui/resources/ui_main_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow ui;
};
