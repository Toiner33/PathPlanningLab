#include "ui/algorithms_settings/astar_settings_dialog.hpp"

AStarSettingsDialog::AStarSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setObjectName(WINDOW_TITLE);
    ui.setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
}