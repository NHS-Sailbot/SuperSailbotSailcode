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
                Logging::Logger::Log(F("deserializeJson() failed: "));
                Logging::Logger::Log(error.c_str());
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

    private:
        const static char* json;
    };
}
