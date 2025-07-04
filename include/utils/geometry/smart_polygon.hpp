#pragma once

#include <optional>
#include <memory>

#include <QGraphicsItem>
#include <QVector>
#include <QPoint>

#include "utils/geometry/poly.hpp"
#include "utils/visuals/polygon_design.hpp"

namespace utils {
namespace geometry {

class SmartPolygon : public QGraphicsPolygonItem {
public:
    using SharedPtr = std::shared_ptr<SmartPolygon>;
    using UniquePtr = std::unique_ptr<SmartPolygon>;

    SmartPolygon(const visuals::PolygonDesign& polygonDesign);
    SmartPolygon(const poly::PolygonType& newPolygon, const visuals::PolygonDesign& polygonDesign);
    SmartPolygon(const QPolygonF& newPolygon, const visuals::PolygonDesign& polygonDesign);

    void addPoint(const QPointF& newPoint);
    void setPreview(const QPointF& simPoint);
    void setDesign(const visuals::PolygonDesign& newDesign);
    void setVisuals(bool preview = true);
    bool finalizePolygon();

private:
    std::optional<QPolygonF> qtPolygon;
    std::optional<poly::PolygonType> boostPolygon;
    visuals::PolygonDesign visualDesign;
};

};  // namespace geometry
};  // namespace utils