#pragma once

#include "ui/algorithms_settings/algorithm_settings_dialog.hpp"

namespace ui {
namespace algorithms_settings {

class DijkstraSettingsDialog : public AlgorithmSettingsDialog {
public:
    DijkstraSettingsDialog(QWidget *parent = nullptr);

private:
    static constexpr const char* WINDOW_TITLE = "Dijkstra Settings";
};

}  // namespace ui
}  // namespace algorithms_settings