#pragma once

#include <memory>
#include <vector>

#include "ui/graphics_scene.hpp"

#include "utils/visuals/polygon_design.hpp"
#include "utils/geometry/smart_polygon.hpp"

namespace utils {
namespace geometry {
    
class SmartMultiPolygon {
public:
    SmartMultiPolygon(const std::shared_ptr<GraphicsScene>& scene);
    ~SmartMultiPolygon();

    void addPolygon(const SmartPolygon::SharedPtr& newPolygon);
    void popPolygon();
    void clear();    
private:
    std::shared_ptr<GraphicsScene> parentScene;
    std::vector<SmartPolygon::SharedPtr> smartPolygons;

    bool performMerge();
};

}; // namespace geometry
}; // namespace utils