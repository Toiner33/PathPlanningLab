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
    QGraphicsPathItem(),
    visualDesign(polygonDesign) {
        setVisuals(true);
        qtPolygonWithRings.setFillRule(Qt::OddEvenFill);
    };

SmartPolygon::SmartPolygon(
    const poly::PolygonType& newPolygon,
    const visuals::PolygonDesign& polygonDesign)
: SmartPolygon(polygonDesign) {
    boostPolygon = newPolygon;
    poly::FailureType correctionResult = poly::correctAndCheck(boostPolygon.value());
    if (correctionResult == poly::FailureType::no_failure) {
        setVisuals(false);
        qtPolygonWithRings = poly::toQPainterPath(boostPolygon.value());
        this->setPath(qtPolygonWithRings);
    } else {
        boostPolygon = std::nullopt;
        qtPolygonPreview = std::nullopt;
        std::cout << "[ERROR] Creating new SmartPolygon: " << 
            boost::geometry::validity_failure_type_message(correctionResult) << std::endl;
    }
};

SmartPolygon::SmartPolygon(
    const QPolygonF& newPolygon,
    const visuals::PolygonDesign& polygonDesign
): SmartPolygon(polygonDesign) {
    boostPolygon = poly::toBoostPolygon(newPolygon);
    poly::FailureType correctionResult = poly::correctAndCheck(boostPolygon.value());
    if (correctionResult == poly::FailureType::no_failure) {
        setVisuals(false);
        qtPolygonWithRings = poly::toQPainterPath(boostPolygon.value());
        this->setPath(qtPolygonWithRings);
    } else {
        boostPolygon = std::nullopt;
        qtPolygonPreview = std::nullopt;
        std::cout << "[ERROR] Creating new SmartPolygon: " << 
            boost::geometry::validity_failure_type_message(correctionResult) << std::endl;
    }
};

void SmartPolygon::addPoint(const QPointF& newPoint) {
    if (!boostPolygon || !qtPolygonPreview) {
        boostPolygon = poly::PolygonType();
        qtPolygonPreview = QPolygonF();
        setVisuals(); 
    }

    QPainterPath previewPolygonPath = QPainterPath();
    qtPolygonPreview->append(newPoint);
    boostPolygon->outer().emplace_back(newPoint.x(), newPoint.y());
    previewPolygonPath.addPolygon(qtPolygonPreview.value());
    previewPolygonPath.closeSubpath();
    this->setPath(previewPolygonPath);
}

void SmartPolygon::setPreview(const QPointF& simPoint) {
    if (!qtPolygonPreview) { return; }
    QPainterPath previewPolygonPath = QPainterPath();
    qtPolygonPreview->append(simPoint);
    previewPolygonPath.addPolygon(qtPolygonPreview.value());
    previewPolygonPath.closeSubpath();
    this->setPath(previewPolygonPath);
    qtPolygonPreview->pop_back();
}

bool SmartPolygon::finalizePolygon() {
    if (!qtPolygonPreview || qtPolygonPreview->size() < 3) {
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

    qtPolygonWithRings.addPath(poly::toQPainterPath(boostPolygon.value()));

    setVisuals(false);
    this->setPath(qtPolygonWithRings);
    qtPolygonPreview = std::nullopt;
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
    qtPolygonWithRings.clear();
    qtPolygonWithRings.addPath(poly::toQPainterPath(boostPolygon.value()));
    this->setPath(qtPolygonWithRings);
    qtPolygonPreview = std::nullopt;
    return true;
}

bool SmartPolygon::isEmpty() const {
    return boostPolygon == std::nullopt;
}

std::vector<SmartPolygon::SharedPtr> SmartPolygon::eraseAndSplit(const SmartPolygon& other) {
    std::vector<poly::PolygonType> differenceResult;
    std::vector<SmartPolygon::SharedPtr> splittedPolygons;
    boost::geometry::difference(
        boostPolygon.value(), other.boostPolygon.value(), differenceResult);

    if (differenceResult.empty()) {
        qtPolygonWithRings.clear();
        this->setPath(qtPolygonWithRings);
        boostPolygon = std::nullopt;
        qtPolygonPreview = std::nullopt;
        std::cout << "The whole polygon was removed!" << std::endl;
        return splittedPolygons;
    }

    boostPolygon = differenceResult.back();
    qtPolygonWithRings.clear();
    qtPolygonWithRings.addPath(poly::toQPainterPath(boostPolygon.value()));
    this->setPath(qtPolygonWithRings);
    differenceResult.pop_back();

    if (differenceResult.empty()) { return splittedPolygons; }

    for (const poly::PolygonType& polygon : differenceResult) {
        splittedPolygons.emplace_back(
            std::make_shared<SmartPolygon>(polygon, visualDesign));
    }

    return splittedPolygons;
}

void SmartPolygon::setDesign(const visuals::PolygonDesign& newDesign) {
    visualDesign = newDesign;
    setVisuals();
}

void SmartPolygon::setVisuals(bool preview) {
    this->setBrush(visualDesign.getBrush(preview));
    this->setPen(visualDesign.getPen(preview));
}

template <typename T>
T SmartPolygon::getCentroid() const {
    if (isEmpty()) {
        return {0.0, 0.0};
    }

    poly::PointType centroid;
    boost::geometry::centroid(boostPolygon.value(), centroid);
    return {centroid.x(), centroid.y()};
}

};  // namespace geometry
};  // namespace utils