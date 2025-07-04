#include "utils/visuals/polygon_design.hpp"

namespace utils {
namespace visuals {

PolygonDesign::PolygonDesign(
    const QColor& mainColor,
    double previewAlpha,
    const QColor& ringsColor
) {
    finalPen = QPen(Qt::black, 1, Qt::SolidLine);
    previewPen = QPen(Qt::black, 1, Qt::DashLine);
    finalBrush = QBrush(mainColor);
    ringsBrush = QBrush(ringsColor);
    previewColor = mainColor;
    previewColor.setAlpha(previewAlpha);
    previewBrush = QBrush(previewColor);
}

PolygonDesign::PolygonDesign(
    const QColor& mainColor,
    const QColor& ringsColor,
    double previewAlpha
): PolygonDesign(mainColor, previewAlpha, ringsColor) { }

void PolygonDesign::setNewAlpha(double previewAlpha) {
    previewColor.setAlpha(previewAlpha);
    previewBrush = QBrush(previewColor);  
}

QPen PolygonDesign::getPen(bool preview) const { 
    return preview ? previewPen : finalPen;
}
QBrush PolygonDesign::getBrush(bool preview) const { 
    return preview ? previewBrush : finalBrush; 
}

QBrush PolygonDesign::getRingsBrush() const {
    return ringsBrush;
}

};  // namespace visuals
};  // namespace utils