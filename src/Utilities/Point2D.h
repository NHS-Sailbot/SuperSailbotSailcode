/// Created by Computery on 6/8/2025.

#pragma once

namespace Utilitys {
    class Point2D {
    public:
        Point2D(double x, double y);
        
        static Point2D subtract(Point2D point1, Point2D point2);
        static Point2D add(Point2D point1, Point2D point2);
        static Point2D multiply(Point2D point, double scalar);
        static double dotProduct(Point2D point1, Point2D point2) ;
        static double crossProduct(Point2D point1, Point2D point2);

        double x;
        double y;
    };
}