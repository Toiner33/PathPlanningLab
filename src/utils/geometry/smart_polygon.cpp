#include <iostream>
#include <optional>
#include <memory>

#include <boost/geometry/algorithms/is_valid.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>

#include <QMessageBox>

#include "utils/geometry/smart_polygon.hpp"

namespace utils {
namespace geometry {

SmartPolygon::SmartPolygon(const visuals::PolygonDesign& polygonDesign): 
    QGraphicsPolygonItem(),
    visualDesign(polygonDesign) {
        setVisuals(true);
    };

SmartPolygon::SmartPolygon(
    const poly::PolygonType& newPolygon,
    const visuals::PolygonDesign& polygonDesign)
: visualDesign(polygonDesign) {
    boostPolygon = newPolygon;
    poly::FailureType correctionResult = poly::correctAndCheck(boostPolygon.value());
    if (correctionResult == poly::FailureType::no_failure) {
        setVisuals(false);
        qtPolygon = poly::toQPolygonF(boostPolygon.value());
        this->setPolygon(qtPolygon.value());
    } else {
        boostPolygon = std::nullopt;
        qtPolygon = std::nullopt;
        std::cout << "[ERROR] Creating new SmartPolygon: " << 
            boost::geometry::validity_failure_type_message(correctionResult) << std::endl;
    }
};

SmartPolygon::SmartPolygon(
    const QPolygonF& newPolygon,
    const visuals::PolygonDesign& polygonDesign
): visualDesign(polygonDesign) {
    boostPolygon = poly::toBoostPolygon(newPolygon);
    poly::FailureType correctionResult = poly::correctAndCheck(boostPolygon.value());
    if (correctionResult == poly::FailureType::no_failure) {
        setVisuals(false);
        qtPolygon = newPolygon;
        this->setPolygon(qtPolygon.value());
    } else {
        boostPolygon = std::nullopt;
        qtPolygon = std::nullopt;
        std::cout << "[ERROR] Creating new SmartPolygon: " << 
            boost::geometry::validity_failure_type_message(correctionResult) << std::endl;
    }
};

void SmartPolygon::addPoint(const QPointF& newPoint) {
    if (!boostPolygon || !qtPolygon) { 
        boostPolygon = poly::PolygonType();
        qtPolygon = QPolygonF();
        setVisuals(); 
    }

    qtPolygon->append(newPoint);
    boostPolygon->outer().emplace_back(newPoint.x(), newPoint.y());
    this->setPolygon(qtPolygon.value());
}

void SmartPolygon::setPreview(const QPointF& simPoint) {
    if (!qtPolygon) { return; }
    qtPolygon->append(simPoint);
    this->setPolygon(qtPolygon.value());
    qtPolygon->pop_back();
}

bool SmartPolygon::finalizePolygon() {
    if (qtPolygon->size() < 3) {
        QMessageBox::warning(nullptr, "Smart Polygon", "Polygon must have at least 3 points!");
        return false;
    }

    boost::geometry::correct(boostPolygon.value());
    boost::geometry::validity_failure_type failure;
    if (!boost::geometry::is_valid(boostPolygon.value(), failure)) {
        QMessageBox::warning(nullptr, "Smart Polygon", "Invalid polygon: " +
            QString(boost::geometry::validity_failure_type_message(failure))
        );
        return false;
    }

    
    setVisuals(false);
    this->setPolygon(qtPolygon.value());
    return true;
}

bool SmartPolygon::intersects(const SmartPolygon& other) const {
    return boost::geometry::intersects(boostPolygon.value(), other.boostPolygon.value());
}

bool SmartPolygon::merge(const SmartPolygon& other) {
    poly::MultiPolygonType mergedPolygons;
    boost::geometry::union_(boostPolygon.value(), other.boostPolygon.value(), mergedPolygons);
    if (mergedPolygons.size() > 1) {
        QMessageBox::warning(nullptr, "Smart Polygon", "Cannot merge not overlapping polygons!");
        return false;
    }

    setVisuals(false);
    boostPolygon = mergedPolygons.front();
    this->setPolygon(poly::toQPolygonF(boostPolygon.value()));
    return true;
}

void SmartPolygon::setDesign(const visuals::PolygonDesign& newDesign) {
    visualDesign = newDesign;
    setVisuals();
}

void SmartPolygon::setVisuals(bool preview) {
    this->setBrush(visualDesign.getBrush(preview));
    this->setPen(visualDesign.getPen(preview));
}

};  // namespace geometry
};  // namespace utils