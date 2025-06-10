// Created by sailbot on 6/10/25.

#pragma once

#include "Electronics/ElectronicsManager.h"
#include "Sailing/Types/AutopilotBase.h"
#include "Waypoint/Waypoint.h"
#include "Waypoint/WaypointManager.h"

using namespace Electronics;

namespace Sailing::Implementations {
    enum TackingState {
        NotInIrons = -1,
        StarboardTack = 0,
        PortTack = 1,
    };

    class PrecisionAutopilot : public Types::AutopilotBase {
    public:
        PrecisionAutopilot() { targetWaypointIndex = 0; }

        int targetWaypointIndex = -1;
        TackingState currentTack = NotInIrons;

        void virtual Update() override {
            double waypointCourse = Waypoints::Waypoint::courseTo(ElectronicsManager::Gps->GetPosition(), Waypoints::WaypointManager::waypoints[targetWaypointIndex].m_Position);
            double relativeWindDirection = GetRelativeWindDirection(waypointCourse);
            bool isTackingNeeded = isRelativeWindDirectionInIrons(relativeWindDirection);

            if (!isTackingNeeded) {
                Logger::Log(F("Not tacking, relative wind direction is not in irons."));
                currentTack = NotInIrons;

                // TODO come back here

                return;
            }

            if (currentTack == NotInIrons) {
                Logger::Log(F("Recalculating course due to tacking being needed."));

            } else {
                // We are already tacking, so we need to check if we are still in irons
            }
        }

        double GetRelativeWindDirection(double bearing) {
            return abs(fmod(m_WindSensor->m_WindDirection - bearing, 360));
        }

        bool isRelativeWindDirectionInIrons(double relativeWindDirection) {
            // TODO make this configurable
            return (relativeWindDirection >= 0 && relativeWindDirection <= 45) || (relativeWindDirection >= 315 && relativeWindDirection <= 360);
        }
    };
}
