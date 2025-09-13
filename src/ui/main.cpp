#include <QApplication>

#include "ui/main_window.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ui::MainWindow window;
    window.show();
    return app.exec();
}