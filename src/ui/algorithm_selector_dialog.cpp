#include <QPushButton>
#include <QObject>

#include "ui/algorithm_selector_dialog.hpp"

AlgorithmSelectorDialog::AlgorithmSelectorDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    algorithmSelectorGroup = std::make_unique<QButtonGroup>(this);
    algorithmSelectorGroup->setExclusive(true);
    algorithmSelectorGroup->addButton(ui.AStarRadioBt);
    algorithmSelectorGroup->addButton(ui.DijkstraRadioBt);

    QObject::connect(ui.AStarSettingsBt, &QPushButton::clicked, &astarSettingsDialog, &AStarSettingsDialog::exec);
    QObject::connect(ui.DijkstraSettingsBt, &QPushButton::clicked, &dijkstraSettingsDialog, &DijkstraSettingsDialog::exec);
}