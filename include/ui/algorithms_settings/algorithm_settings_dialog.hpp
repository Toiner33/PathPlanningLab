#pragma once

#include <QDialog>

#include "ui/algorithms_settings/types.hpp"
#include "ui/algorithms_settings/mappings.hpp"

#include "ui/resources/algorithm_settings_dialog.h"

namespace ui {
namespace algorithms_settings {

class AlgorithmSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    AlgorithmSettingsDialog(QWidget *parent = nullptr, const char* title = "Unknown Settings");
    virtual ~AlgorithmSettingsDialog() = default;

    Ui::SettingsDialog& getUi() { return ui; }

    types::DiscretizationMethod getDiscretizationMethod() const;
private:
    Ui::SettingsDialog ui;
};

}  // namespace algorithms_settings
}  // namespace ui
