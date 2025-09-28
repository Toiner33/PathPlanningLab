#include <iostream>
#include <iterator>

#include "utils/geometry/smart_multi_polygon.hpp"

namespace utils {
namespace geometry {
    
SmartMultiPolygon::SmartMultiPolygon(const std::shared_ptr<ui::GraphicsScene>& scene):
    parentScene(scene) { };

SmartMultiPolygon::~SmartMultiPolygon() {
    clear();
    parentScene.reset();
}

void SmartMultiPolygon::addPolygon(const SmartPolygon::SharedPtr& newPolygon){
    smartPolygons.push_back(newPolygon);
    parentScene->addItem(newPolygon.get());
}

void SmartMultiPolygon::addPolygon(SmartPolygon::SharedPtr&& newPolygon) {
    smartPolygons.push_back(std::move(newPolygon));
    parentScene->addItem(smartPolygons.back().get()); 
}

void SmartMultiPolygon::popPolygon(){
    parentScene->removeItem(smartPolygons.back().get());
    smartPolygons.pop_back();
}
void SmartMultiPolygon::clear(){
    while (!smartPolygons.empty()) { popPolygon(); }
}

bool SmartMultiPolygon::empty() const {
    return smartPolygons.empty();
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

bool SmartMultiPolygon::eraseOverlapping(const SmartPolygon& eraserPolygon) {
    auto lastSmartPolygonIt = smartPolygons.end();
    auto smartPolygonIt = smartPolygons.begin();
    bool erasedPolygon = false;

    while (smartPolygonIt != lastSmartPolygonIt) {
        if (!smartPolygonIt->get()->intersects(eraserPolygon)) {
            ++smartPolygonIt;
            continue;
        }

        erasedPolygon = true;

        std::vector<utils::geometry::SmartPolygon::SharedPtr> splittedPolygons =
            smartPolygonIt->get()->eraseAndSplit(eraserPolygon);

        if (smartPolygonIt->get()->isEmpty()) {
            parentScene->removeItem(smartPolygonIt->get());
            smartPolygonIt = smartPolygons.erase(smartPolygonIt);
            continue;
        }

        for (utils::geometry::SmartPolygon::SharedPtr& polygon : splittedPolygons) {
            addPolygon(std::move(polygon));
        }

        ++smartPolygonIt;
    }
    return erasedPolygon;
}

}; // namespace geometry
}; // namespace utils