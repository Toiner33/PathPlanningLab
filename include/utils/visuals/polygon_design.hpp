#pragma once

#include <QPen>
#include <QBrush>

namespace utils {
namespace visuals {

class PolygonDesign {
public:
    PolygonDesign(
        const QColor& mainColor,
        double previewAlpha = 100,
        const QColor& ringsColor = Qt::transparent
    );

    PolygonDesign(
        const QColor& mainColor,
        const QColor& ringsColor,
        double previewAlpha = 100
    );

    void setNewAlpha(double previewAlpha);
    QPen getPen(bool preview = false) const;
    QBrush getBrush(bool preview = false) const;
    QBrush getRingsBrush() const;

private:
    QPen finalPen;
    QPen previewPen;
    QBrush finalBrush;
    QBrush previewBrush;
    QBrush ringsBrush;

    QColor previewColor;
};

};  // namespace visuals
};  // namespace utils