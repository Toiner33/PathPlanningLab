#pragma once

#include <optional>
#include <memory>

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QVector>
#include <QPoint>

#include "utils/geometry/poly.hpp"
#include "utils/visuals/polygon_design.hpp"

namespace utils {
namespace geometry {

class SmartPolygon : public QGraphicsPathItem {
public:
    using SharedPtr = std::shared_ptr<SmartPolygon>;
    using ConstSharedPtr = std::shared_ptr<const SmartPolygon>;
    using UniquePtr = std::unique_ptr<SmartPolygon>;

    SmartPolygon(const visuals::PolygonDesign& polygonDesign);
    SmartPolygon(const poly::PolygonType& newPolygon, const visuals::PolygonDesign& polygonDesign);
    SmartPolygon(const QPolygonF& newPolygon, const visuals::PolygonDesign& polygonDesign);

    void addPoint(const QPointF& newPoint);
    void setPreview(const QPointF& simPoint);
    void setDesign(const visuals::PolygonDesign& newDesign);
    void setVisuals(bool preview = true);
    bool finalizePolygon();

    bool intersects(const SmartPolygon& other) const;
    bool merge(const SmartPolygon& other);

private:
    QPainterPath qtPolygonWithRings;
    visuals::PolygonDesign visualDesign;

    std::optional<QPolygonF> qtPolygonPreview;
    std::optional<poly::PolygonType> boostPolygon;
};

};  // namespace geometry
};  // namespace utils