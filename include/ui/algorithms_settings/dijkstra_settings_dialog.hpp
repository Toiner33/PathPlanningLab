#ifndef DIJKSTRA_SETTINGS_DIALOG_HPP
#define DIJKSTRA_SETTINGS_DIALOG_HPP

#include <QDialog>

#include "ui/resources/algorithm_settings_dialog.h"

class DijkstraSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DijkstraSettingsDialog(QWidget *parent = nullptr);

private:
    static constexpr const char* WINDOW_TITLE = "Dijkstra Settings";

    Ui::SettingsDialog ui;
};

#endif // DIJKSTRA_SETTINGS_DIALOG_HPP
