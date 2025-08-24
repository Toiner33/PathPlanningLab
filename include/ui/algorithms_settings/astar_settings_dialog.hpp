#ifndef ASTAR_SETTINGS_DIALOG_HPP
#define ASTAR_SETTINGS_DIALOG_HPP

#include <QDialog>

#include "ui/resources/algorithm_settings_dialog.h"

class AStarSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AStarSettingsDialog(QWidget *parent = nullptr);

private:
    static constexpr const char* WINDOW_TITLE = "AStar Settings";

    Ui::SettingsDialog ui;
};

#endif // ASTAR_SETTINGS_DIALOG_HPP
