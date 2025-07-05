#pragma once

#include <QPen>
#include <QBrush>

namespace utils {
namespace visuals {

class PolygonDesign {
public:
    PolygonDesign(
        const QColor& mainColor,
        double previewAlpha = 100
    );

    void setNewAlpha(double previewAlpha);
    QPen getPen(bool preview = false) const;
    QBrush getBrush(bool preview = false) const;

private:
    QPen finalPen;
    QPen previewPen;
    QBrush finalBrush;
    QBrush previewBrush;
    QColor previewColor;
};

};  // namespace visuals
};  // namespace utils