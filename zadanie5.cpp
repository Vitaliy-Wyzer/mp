#include <iostream>
#include <cmath>
#include <stdexcept>

class Point {
    double x, y, z;

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    double operator[](int index) const {
        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Index out of range");
        }
    }

    double distance(const Point& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y, z - other.z);
    }

    Point operator*(double scalar) const {
        return Point(x * scalar, y * scalar, z * scalar);
    }

    friend Point operator*(double scalar, const Point& point) {
        return point * scalar;
    }

    bool operator==(const Point& other) const {
        return std::abs(distance(Point()) - other.distance(Point())) < 1e-10;
    }

    bool operator<(const Point& other) const {
        return distance(Point()) < other.distance(Point());
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& point) {
        return is >> point.x >> point.y >> point.z;
    }
};

int main() {
    double coords[2][3] = {{1.0, 1.0, 1.0}, {1.0, 2.0, 3.0}};
    Point p1(coords[0][0], coords[0][1], coords[0][2]);
    Point p2(coords[1][0], coords[1][1], coords[1][2]);
    const Point p3(0.4, 0.2, 0.1);

    std::cout << p1 << ", " << p2 << '\n';
    std::cout << p3[0] << ' ' << p3[1] << ' ' << p3[2] << '\n';
    std::cout << p1.distance(Point()) << ", " << p3.distance(p1) << '\n';
    std::cout << p1 + p2 << ", " << p1 - p3 << '\n';
    std::cout << 3.14 * p2 << ", " << p2 * 3.14 << '\n';
    std::cout << (p1 < p3) << ", " << (p1 == Point(1.0, 1.0, 1.0)) << '\n';
    std::cin >> p1;
    std::cout << p1 << '\n';

    return 0;
}
