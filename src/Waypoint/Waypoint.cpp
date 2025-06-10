/// Created by Computery on 6/8/2025.

#include "Waypoint.h"
#include <Arduino.h>
#include "Constants.h"

namespace Waypoints {
    Waypoint::Waypoint(double latitude, double longitude, long radius = 5) : m_Position(Utilitys::Point2D(latitude, longitude)) {
        m_Radius = radius;
    }

    double Waypoint::courseTo(const Utilitys::Point2D& point1, const Utilitys::Point2D& point2) {
        return courseTo(point1.x, point1.y, point2.x, point2.y);
    }
    double Waypoint::courseTo(const Waypoint& waypoint1, const Waypoint& waypoint2) {
        return courseTo(waypoint1.getLatitude(), waypoint1.getLongitude(), waypoint2.getLatitude(), waypoint2.getLongitude());
    }
    // https://github.com/mikalhart/TinyGPSPlus/blob/master/src/TinyGPS%2B%2B.cpp I stole this from here.
    double Waypoint::courseTo(double latitude1, double longitude1, double latitude2, double longitude2) {
        // returns course in degrees (North=0, West=270) from position 1 to position 2,
        // both specified as signed decimal-degrees latitude and longitude.
        // Because Earth is no exact sphere, calculated course may be off by a tiny fraction.
        // Courtesy of Maarten Lamers
        double dlon = radians(longitude2 - longitude1);
        latitude1 = radians(latitude1);
        latitude2 = radians(latitude2);
        double a1 = sin(dlon) * cos(latitude2);
        double a2 = sin(latitude1) * cos(latitude2) * cos(dlon);
        a2 = cos(latitude1) * sin(latitude2) - a2;
        a2 = atan2(a1, a2);
        if (a2 < 0.0)
        {
            a2 += TWO_PI;
        }
        return degrees(a2);
    }

    double Waypoint::distanceBetween(const Utilitys::Point2D& point1, const Utilitys::Point2D& point2) {
        return distanceBetween(point1.x, point1.y, point2.x, point2.y);
    }
    double Waypoint::distanceBetween(const Waypoint& waypoint1, const Waypoint& waypoint2) {
        return distanceBetween(waypoint1.getLatitude(), waypoint1.getLongitude(), waypoint2.getLatitude(), waypoint2.getLongitude());
    }
    // https://github.com/mikalhart/TinyGPSPlus/blob/master/src/TinyGPS%2B%2B.cpp I stole this from here.
    double Waypoint::distanceBetween(double latitude1, double longitude1, double latitude2, double longitude2) {
        // returns distance in meters between two positions, both specified
        // as signed decimal-degrees latitude and longitude. Uses great-circle
        // distance computation for hypothetical sphere of radius 6371009 meters.
        // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
        // Courtesy of Maarten Lamers
        double delta = radians(longitude1 - longitude2);
        double sdlong = sin(delta);
        double cdlong = cos(delta);
        latitude1 = radians(latitude1);
        latitude2 = radians(latitude2);
        double slat1 = sin(latitude1);
        double clat1 = cos(latitude1);
        double slat2 = sin(latitude2);
        double clat2 = cos(latitude2);
        delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
        delta = sq(delta);
        delta += sq(clat2 * sdlong);
        delta = sqrt(delta);
        double denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
        delta = atan2(delta, denom);
        return delta * Constants::RADIUS_OF_EARTH;
    }

    bool Waypoint::pointIsInRadius(const Utilitys::Point2D& point) const {
        return distanceBetween(m_Position, point) <= m_Radius;
    }
}
