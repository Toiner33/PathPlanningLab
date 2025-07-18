#include "utils/visuals/polygon_design.hpp"

namespace utils {
namespace visuals {

PolygonDesign::PolygonDesign(
    const QColor& mainColor,
    double previewAlpha
) {
    finalPen = QPen(Qt::black, 1, Qt::SolidLine);
    previewPen = QPen(Qt::black, 1, Qt::DashLine);
    finalBrush = QBrush(mainColor);
    previewColor = mainColor;
    previewColor.setAlpha(previewAlpha);
    previewBrush = QBrush(previewColor);
}

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

};  // namespace visuals
};  // namespace utils