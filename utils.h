#ifndef UTILITY_H
#define UTILITY_H

namespace evol {

struct Vector {
    double x{0.0};
    double y{0.0};
    [[nodiscard]] double length() const;
    Vector operator+(const Vector& v_) const;
    Vector operator-(const Vector& v_) const;
    bool operator>=(const Vector& v_) const;
    bool operator<(const Vector& v_) const;
};

struct Rectangle {
    Vector topLeft{};
    Vector bottomRight{};
    double width() const;
    double height() const;
    bool contains(const Rectangle& rectangle_) const;
    bool intersects(const Rectangle& rectangle_) const;
    static const Rectangle INF;
};

}

#endif // UTILITY_H
