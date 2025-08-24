#ifndef ALGORITHM_SELECTOR_DIALOG_HPP
#define ALGORITHM_SELECTOR_DIALOG_HPP

#include <memory>

#include <QDialog>
#include <QButtonGroup>

#include "ui/resources/algorithm_selector_dialog.h"

#include "ui/algorithms_settings/astar_settings_dialog.hpp"
#include "ui/algorithms_settings/dijkstra_settings_dialog.hpp"

class AlgorithmSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmSelectorDialog(QWidget *parent = nullptr);

private:
    Ui::algorithmsDialog ui;
    AStarSettingsDialog astarSettingsDialog;
    DijkstraSettingsDialog dijkstraSettingsDialog;

    std::unique_ptr<QButtonGroup> algorithmSelectorGroup;
};

#endif // ALGORITHM_SELECTOR_DIALOG_HPP
