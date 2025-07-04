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

bool SmartMultiPolygon::performMerge(){

}

}; // namespace geometry
}; // namespace utils