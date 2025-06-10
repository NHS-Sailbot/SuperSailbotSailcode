/// Created by Computery on 6/8/2025.

#include "Point2D.h"

namespace Utilitys {
    Point2D::Point2D(double x, double y) : x(x), y(y) {}

    Point2D Point2D::subtract(const Point2D& point1, const Point2D& point2) {
        return {point1.x - point2.x, point1.y - point2.y};
    }

    Point2D Point2D::add(const Point2D& point1, const Point2D& point2) {
        return {point1.x + point2.x, point1.y + point2.y};
    }

    Point2D Point2D::multiply(const Point2D& point, double scalar) {
        return {point.x * scalar, point.y * scalar};
    }

    double Point2D::dotProduct(const Point2D& point1, const Point2D& point2) {
        return point1.x * point2.x + point1.y * point2.y;
    }

    double Point2D::crossProduct(const Point2D& point1, const Point2D& point2) {
        return point1.x * point2.y - point1.y * point2.x;
    }
}