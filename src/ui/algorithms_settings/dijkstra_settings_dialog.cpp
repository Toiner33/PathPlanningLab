#include "ui/algorithms_settings/dijkstra_settings_dialog.hpp"

DijkstraSettingsDialog::DijkstraSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setObjectName(WINDOW_TITLE);
    ui.setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
}