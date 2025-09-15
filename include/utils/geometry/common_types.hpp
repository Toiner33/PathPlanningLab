#pragma once

namespace utils {
namespace geometry {

struct Point{
    double x;
    double y;
};

struct Box {
    Point max;
    Point min;
    Point center() const { 
        return {
            (max.x + min.x) * 0.5,
            (max.y + min.y) * 0.5
        }; 
}
};
 
}; // namespace geometry
}; // namespace utils