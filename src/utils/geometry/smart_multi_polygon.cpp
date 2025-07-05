#include "utils/geometry/smart_multi_polygon.hpp"

namespace utils {
namespace geometry {
    
SmartMultiPolygon::SmartMultiPolygon(const std::shared_ptr<GraphicsScene>& scene):
    parentScene(scene) { };

SmartMultiPolygon::~SmartMultiPolygon() {
    clear();
    parentScene.reset();
}

void SmartMultiPolygon::addPolygon(const SmartPolygon::SharedPtr& newPolygon){
    smartPolygons.push_back(newPolygon);
    parentScene->addItem(newPolygon.get());
}
void SmartMultiPolygon::popPolygon(){
    parentScene->removeItem(smartPolygons.back().get());
    smartPolygons.pop_back();
}
void SmartMultiPolygon::clear(){
    while (!smartPolygons.empty()) { popPolygon(); }
}

bool SmartMultiPolygon::mergeOverlapping() {
    auto getIntersectingPolygonIt = [
        &smartPolygons = smartPolygons
    ](){
        return std::find_if(
            std::next(smartPolygons.rbegin()),
            smartPolygons.rend(),
            [&lastPolygon = smartPolygons.back()](
                const SmartPolygon::SharedPtr& polygon
            ) {
                return polygon->intersects(*lastPolygon);
            }
        );
    };
    
    auto intersectingPolygonIt = getIntersectingPolygonIt();
    bool mergedPolygons = intersectingPolygonIt != smartPolygons.rend();

    while (intersectingPolygonIt != smartPolygons.rend()) {
        intersectingPolygonIt->get()->merge(*smartPolygons.back());
        popPolygon();
        intersectingPolygonIt = getIntersectingPolygonIt();
    }

    return mergedPolygons;
}

}; // namespace geometry
}; // namespace utils