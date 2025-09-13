#include <memory>

#include <QPushButton>
#include <QObject>

#include "ui/algorithm_selector_dialog.hpp"

namespace ui {

AlgorithmSelectorDialog::AlgorithmSelectorDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    astarSettingsDialog = std::make_unique<algorithms_settings::AStarSettingsDialog>(parent);
    dijkstraSettingsDialog = std::make_unique<algorithms_settings::DijkstraSettingsDialog>(parent);

    algorithmSelectorGroup = std::make_unique<QButtonGroup>(this);
    algorithmSelectorGroup->setExclusive(true);
    algorithmSelectorGroup->addButton(ui.AStarRadioBt);
    algorithmSelectorGroup->addButton(ui.DijkstraRadioBt);

    QObject::connect(ui.AStarSettingsBt, &QPushButton::clicked, astarSettingsDialog.get(), &algorithms_settings::AStarSettingsDialog::exec);
    QObject::connect(ui.DijkstraSettingsBt, &QPushButton::clicked, dijkstraSettingsDialog.get(), &algorithms_settings::DijkstraSettingsDialog::exec);
}

}  // namespace ui
