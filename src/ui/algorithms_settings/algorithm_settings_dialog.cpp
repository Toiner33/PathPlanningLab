#include <iostream>

#include "ui/algorithms_settings/algorithm_settings_dialog.hpp"

namespace ui {
namespace algorithms_settings {

AlgorithmSettingsDialog::AlgorithmSettingsDialog(QWidget *parent, const char* title)
    : QDialog(parent)
{
    this->setObjectName(title);
    ui.setupUi(this);
    this->setWindowTitle(title);
}

types::DiscretizationMethod AlgorithmSettingsDialog::getDiscretizationMethod() const {
    const std::string& method = ui.comboBox->currentText().toStdString();
    auto it = mappings::stringToDiscretizationMethods.find(method);
    if (it != mappings::stringToDiscretizationMethods.end()) {
        return it->second;
    }

    std::cout << "Uknown discretization method: " << method << std::endl;
    return types::DiscretizationMethod::NONE;
}

}  // namespace algorithms_settings
}  // namespace ui
