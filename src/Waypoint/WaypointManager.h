// Created by sailbot on 6/10/25.

#pragma once

#include <vector>
#include "Waypoint.h"
#include <ArduinoJson.h>
#include "Logging/Logger.h"

using namespace Logging;

namespace Waypoints {
    class WaypointManager {
    public:
        inline static std::vector<Waypoint> waypoints;
        inline static std::vector<Point2D> restrictedAreas;

        static void Start() {
            waypoints.clear();
            restrictedAreas.clear();

            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, json);
            if (error) {
                Logger::Log(F("deserializeJson() failed: "));
                Logger::Log(error.c_str());
                return;
            }

            for (JsonObject wp : doc["waypoints"].as<JsonArray>()) {
                double lat = wp["lat"];
                double lng = wp["lng"];
                waypoints.emplace_back(lat, lng, 5); // radius 0 as not in JSON
            }
            for (JsonObject ra : doc["restrictedArea"].as<JsonArray>()) {
                double lat = ra["lat"];
                double lng = ra["lng"];
                restrictedAreas.emplace_back(lat, lng);
            }

            // Log the number of waypoints and restricted areas loaded
            Logger::Log(F("Loaded "), false);
            Logger::Log(String(waypoints.size()), false);
            Logger::Log(F(" waypoints and "), false);
            Logger::Log(String(restrictedAreas.size()), false);
            Logger::Log(F(" restricted area nodes."));
        }

        static double DistanceToRestrictedArea(const Point2D& position, double heading) {
            bool foundIntersection = false;
            Point2D intersection = FindIntersectionWithRestrictedArea(position, heading, foundIntersection);
            if (foundIntersection) { return Waypoint::distanceBetween(position, intersection); }
            return -1;
        }

        static Point2D FindIntersectionWithRestrictedArea(const Point2D& rayOrigin, double heading, bool& foundIntersection) {
            // For future reference, this doesn't account for the curvature of the earth. but that shouldn't matter for our purposes!
            heading = radians(heading);
            foundIntersection = false;

            int restrictedAreaCount = restrictedAreas.size();
            for (int i = 0; i < restrictedAreaCount; i++) {
                double distance = GetDistanceToLineIntersection (
                        restrictedAreas[i],
                        restrictedAreas[(i + 1) % restrictedAreaCount],
                        rayOrigin,
                        heading,
                        foundIntersection
                );
                if (foundIntersection) {
                    // Create point at intersection then find distance in meters.
                    return Point2D::add(rayOrigin, Point2D::multiply(Point2D(sin(heading),cos(heading)), distance));
                }
            }
            return {0,0};
        }

        static double GetDistanceToLineIntersection(const Point2D& LinePointOne, const Point2D& LinePointTwo, const Point2D& rayOrigin, double heading, bool &foundIntersection) {
            foundIntersection = false;

            Point2D lineToStartPoint = Point2D::subtract(rayOrigin, LinePointOne);
            Point2D lineSegment = Point2D::subtract(LinePointTwo, LinePointOne);

            // Okay so the cos and sin are used like this since north is 0 degrees.
            Point2D rayDirection = Point2D(-cos(heading), sin(heading));

            // dotProductOfSegmentAndRay - This represents the dot product of the line segment vector and the ray direction vector. It is used to check if the line segment and the ray are orthogonal.
            double dotProductOfSegmentAndRay = Point2D::dotProduct(lineSegment, rayDirection);
            if (abs(dotProductOfSegmentAndRay) < 0.000001) {
                return -1;
            }

            // This scalar factor represents how far along the ray the intersection point is.
            double rayIntersectionFactor = Point2D::crossProduct(lineSegment, lineToStartPoint) / dotProductOfSegmentAndRay;
            // This scalar factor represents how far along the line segment the intersection point is.
            double segmentIntersectionFactor = Point2D::dotProduct(lineToStartPoint, rayDirection) / dotProductOfSegmentAndRay;

            if (rayIntersectionFactor >= 0.0 && (segmentIntersectionFactor >= 0.0 && segmentIntersectionFactor <= 1.0)) {
                foundIntersection = true;
                return rayIntersectionFactor;
            }
            return -1;
        }

    private:
        const static char* json;
    };
}
