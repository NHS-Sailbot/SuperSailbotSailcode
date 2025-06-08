/// Created by Computery on 6/8/2025.

#pragma once

#include "Utilities/Point2D.h"

namespace Waypoints {
    class Waypoint {
    public:
        Waypoint(double latitude, double longitude, long radius);

        double getLatitude() const { return m_Position.x; }
        double getLongitude() const { return m_Position.y; }
        Utilitys::Point2D m_Position;
        long m_Radius;

        static double courseTo(Utilitys::Point2D point1, Utilitys::Point2D point2);
        static double courseTo(Waypoint waypoint1, Waypoint waypoint2);
        static double courseTo(double latitude1, double longitude1, double latitude2, double longitude2);

        static double distanceBetween(Utilitys::Point2D point1, Utilitys::Point2D point2);
        static double distanceBetween(Waypoint waypoint1, Waypoint waypoint2);
        static double distanceBetween(double latitude1, double longitude1, double latitude2, double longitude2);
    };
}