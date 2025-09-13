#pragma once

#include <memory>

#include <QDialog>
#include <QButtonGroup>

#include "ui/algorithms_settings/algorithm_settings_dialog.hpp"
#include "ui/algorithms_settings/astar_settings_dialog.hpp"
#include "ui/algorithms_settings/dijkstra_settings_dialog.hpp"

#include "ui/resources/algorithm_selector_dialog.h"

namespace ui {

class AlgorithmSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmSelectorDialog(QWidget *parent = nullptr);

private:
    Ui::algorithmsDialog ui;
    std::unique_ptr<algorithms_settings::AlgorithmSettingsDialog> astarSettingsDialog;
    std::unique_ptr<algorithms_settings::AlgorithmSettingsDialog> dijkstraSettingsDialog;

    std::unique_ptr<QButtonGroup> algorithmSelectorGroup;
};

}  // namespace ui
