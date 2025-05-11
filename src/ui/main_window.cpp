#include <QMessageBox>

#include "ui/main_window.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Path Planning", "Running algorithm!");
    });
}

MainWindow::~MainWindow() {}