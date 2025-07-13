#pragma once

#include <memory>
#include <list>

#include "ui/graphics_scene.hpp"

#include "utils/visuals/polygon_design.hpp"
#include "utils/geometry/smart_polygon.hpp"

namespace utils {
namespace geometry {
    
class SmartMultiPolygon {
public:
    SmartMultiPolygon(const std::shared_ptr<GraphicsScene>& scene);
    ~SmartMultiPolygon();

    const SmartPolygon::ConstSharedPtr back() const { return smartPolygons.back(); }
    
    void addPolygon(const SmartPolygon::SharedPtr& newPolygon);
    void addPolygon(SmartPolygon::SharedPtr&& newPolygon);
    void popPolygon();
    void clear();
    
    bool mergeOverlapping();
    bool eraseOverlapping(const SmartPolygon& eraserPolygon);
private:
    std::shared_ptr<GraphicsScene> parentScene;
    std::list<SmartPolygon::SharedPtr> smartPolygons;
};

}; // namespace geometry
}; // namespace utils