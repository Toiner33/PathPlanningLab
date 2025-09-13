#pragma once

#include <map>
#include <string>

#include "ui/algorithms_settings/types.hpp"

namespace ui {
namespace algorithms_settings {
namespace mappings {
inline const std::map<std::string, types::DiscretizationMethod> stringToDiscretizationMethods = {
    { "Occupancy Grid", types::DiscretizationMethod::OCCUPANCY_GRID },
    { "Triangulation", types::DiscretizationMethod::TRIANGULATION },
    { "Quadtree", types::DiscretizationMethod::QUADTREE },
    { "None", types::DiscretizationMethod::NONE }
};
}
}
}