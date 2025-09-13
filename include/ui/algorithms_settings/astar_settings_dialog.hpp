#pragma once

#include "ui/algorithms_settings/algorithm_settings_dialog.hpp"

namespace ui {
namespace algorithms_settings {

class AStarSettingsDialog : public AlgorithmSettingsDialog {
public:
    AStarSettingsDialog(QWidget *parent = nullptr);

private:
    static constexpr const char* WINDOW_TITLE = "AStar Settings";
};

}  // namespace ui
}  // namespace algorithms_settings
