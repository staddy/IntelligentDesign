#include "utils.h"

#include <functional>
#include <cmath>

namespace evol {

double Vector::length() const {
    return std::sqrt(x * x + y * y);
}

Vector Vector::operator+(const Vector& v_) const {
    return Vector{x + v_.x, y + v_.y};
}

Vector Vector::operator-(const Vector& v_) const {
    return Vector{x - v_.x, y - v_.y};
}

bool Vector::operator>=(const Vector& v_) const {
    return std::tie(x, y) >= std::tie(v_.x, v_.y);
}

bool Vector::operator<(const Vector& v_) const {
    return std::tie(x, y) < std::tie(v_.x, v_.y);
}

double Rectangle::width() const {
    return bottomRight.x - topLeft.x;
}

double Rectangle::height() const {
    return bottomRight.y - topLeft.y;
}

bool Rectangle::contains(const Rectangle& rectangle_) const {
    return (rectangle_.topLeft >= topLeft) &&
            (rectangle_.bottomRight < bottomRight);
}

bool Rectangle::intersects(const Rectangle& rectangle_) const {
    return !((rectangle_.bottomRight.x <= topLeft.x) || (rectangle_.topLeft.x >= bottomRight.x) ||
            (rectangle_.bottomRight.y <= topLeft.y) || (rectangle_.topLeft.y >= bottomRight.y));
}

const Rectangle Rectangle::INF{{-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()},
                               {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()}};


}
