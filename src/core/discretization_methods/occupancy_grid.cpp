#include "core/discretization_methods/occupancy_grid.hpp"

namespace core {
namespace discretization_methods {

OccupancyGrid::OccupancyGrid(double userWidth, double userHeight, double resolution, UG::Point centerInWorld): 
    resolution(resolution),
    currentLayer(0) {
    // Adjust the width and height to be a multiple of the resolution
    this->width = std::ceil(userWidth / resolution) * resolution;
    this->height = std::ceil(userHeight / resolution) * resolution;
    this->numRows = this->height / resolution;
    this->numCols = this->width / resolution;
    this->numCells = numRows * numCols;
    this->center.x = this->width * 0.5;
    this->center.y = this->height * 0.5;
    // Origin is at the top left of the grid
    originInWorld.x = centerInWorld.x - (width * 0.5);
    originInWorld.y = centerInWorld.y + (height * 0.5);
    // Add 0 layer with default value
    layers.push_back(std::vector<double>(numCells, DEFAULT_VALUE));
}

OccupancyGrid::OccupancyGrid(double userWidth, double userHeight, double resolution):
    OccupancyGrid(userWidth, userHeight, resolution, {0.0, 0.0}) {}

OccupancyGrid::OccupancyGrid(const UG::Box& gridExtents, int resolution):
    OccupancyGrid(
        gridExtents.max.x - gridExtents.min.x,
        gridExtents.max.y - gridExtents.min.y,
        resolution,
        gridExtents.center()
    ) {}

UG::Point OccupancyGrid::getCenter() const {
    return toWorldCoordinates(this->center);
}

bool OccupancyGrid::setCurrentLayer(size_t layer) {
    if (layer >= layers.size()) { return false; }
    currentLayer = layer;
    return true;
}

UG::Point OccupancyGrid::toGridCoordinates(const UG::Point& point) const {
    return {
        point.x - originInWorld.x,
        point.y - originInWorld.y
    };
}

OccupancyGrid::Cell OccupancyGrid::toGridCell(const UG::Point& point) const {
    UG::Point pointInGrid = toGridCoordinates(point);
    return {
        static_cast<int>(std::floor(pointInGrid.y / resolution)),
        static_cast<int>(std::floor(pointInGrid.x / resolution))
    };
}

double& OccupancyGrid::at(const OccupancyGrid::Cell& gridCell) { 
    return layers.at(currentLayer).at(gridCellToIndex(gridCell)); 
}

double OccupancyGrid::at(const OccupancyGrid::Cell& gridCell) const { 
    return layers.at(currentLayer).at(gridCellToIndex(gridCell)); 
}

// === Private definitions ===

size_t OccupancyGrid::gridCellToIndex(const Cell& gridCell) const {
    return gridCell.row * numCols + gridCell.cell;
}

UG::Point OccupancyGrid::toWorldCoordinates(const UG::Point& point) const {
    return {
        originInWorld.x + point.x,
        originInWorld.y + point.y
    };
}

}  // namespace discretization_methods
}  // namespace core