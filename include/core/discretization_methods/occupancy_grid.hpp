#pragma once

#include <vector>
#include <array>
#include <cmath>

#include "utils/geometry/common_types.hpp"

namespace core {
namespace discretization_methods {

namespace UG = utils::geometry;

class OccupancyGrid {
public:
    static constexpr double DEFAULT_VALUE = -1.0;
    struct Cell { int row, cell; };

    OccupancyGrid(double userWidth, double userHeight, double resolution, UG::Point centerInWorld);
    OccupancyGrid(double userWidth, double userHeight, double resolution);
    OccupancyGrid(const UG::Box& gridExtents, int resolution);

    bool setCurrentLayer(size_t layer);

    UG::Point getCenter() const;
    UG::Point toGridCoordinates(const UG::Point& point) const;
    Cell toGridCell(const UG::Point& point) const;

    double& at(const Cell& gridCell);
    double at(const Cell& gridCell) const;
    double at(size_t layer, const Cell& gridCell);
    double at(size_t layer, const Cell& gridCell) const;

private:
    int width;
    int height;
    int resolution;
    int numRows;
    int numCols;
    int numCells;

    size_t currentLayer;
    std::vector<std::vector<double>> layers;

    UG::Point center;
    UG::Point originInWorld;

    size_t gridCellToIndex(const Cell& gridCell) const;
    UG::Point toWorldCoordinates(const UG::Point& point) const;
};

}  // namespace discretization_methods
}  // namespace core