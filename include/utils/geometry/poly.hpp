#pragma once

#include <QPolygonF>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>

namespace utils {
namespace geometry {
namespace poly {
 
using PointType = boost::geometry::model::d2::point_xy<double>;
using PolygonType = boost::geometry::model::polygon<PointType>;
using MultiPolygonType = boost::geometry::model::multi_polygon<PolygonType>;
using FailureType = boost::geometry::validity_failure_type;
    
inline static FailureType correctAndCheck(
    PolygonType& polygonToCheck
) {
    boost::geometry::correct(polygonToCheck);
    boost::geometry::validity_failure_type failureType;
    boost::geometry::is_valid(polygonToCheck, failureType);
    return failureType;
}

inline static QPolygonF toQPolygonF(const PolygonType& polygon) {
    QPolygonF qPolygon;
    for (const PointType& point : polygon.outer()) {
        qPolygon.append(QPointF(point.x(), point.y()));
    }
    return qPolygon;
}

inline static PolygonType toBoostPolygon(const QPolygonF& qPolygon) {
    PolygonType polygon;
    for (const QPointF& point : qPolygon) {
        polygon.outer().push_back(PointType(point.x(), point.y()));
    }

    return polygon;
}

}; // namespace bpoly   
}; // namespace geometry
}; // namespace utils