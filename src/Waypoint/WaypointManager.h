// Created by sailbot on 6/10/25.

#pragma once

#include <vector>
#include "Waypoint.h"
#include <ArduinoJson.h>

#include "Logging/Logger.h"

namespace Waypoints {
    class WaypointManager {
    public:
        inline static std::vector<Waypoint> waypoints;
        inline static std::vector<Utilitys::Point2D> restrictedAreas;

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
        }

    private:
        static const char* json;
    };
}
