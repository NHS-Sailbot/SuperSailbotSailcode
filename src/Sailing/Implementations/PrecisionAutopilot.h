// Created by sailbot on 6/10/25.

#pragma once

#include "Electronics/ElectronicsManager.h"
#include "Sailing/Types/AutopilotBase.h"
#include "Waypoint/Waypoint.h"
#include "Waypoint/WaypointManager.h"

using namespace Electronics;
using namespace Waypoints;
using namespace Logging;

namespace Sailing::Implementations {
    enum TackingState {
        NotInIrons = -1,
        StarboardTack = 0,
        PortTack = 1,
    };

    class PrecisionAutopilot : public Types::AutopilotBase {
    public:
        PrecisionAutopilot(double inIronsAngle = 45.0, double distanceToChangeTack = 10.0, double allowedHeadingError = 5.0, double allowedSailOutError = 1.0, double maxRudderAngle = 45.0) {
            m_InIronsAngle = inIronsAngle;
            m_DistanceToChangeTack = distanceToChangeTack;
            m_AllowedHeadingError = allowedHeadingError;
            m_AllowedSailOutError = allowedSailOutError;
            m_MaxRudderAngle = maxRudderAngle;

            // Initialize the first waypoint index
            if (!WaypointManager::waypoints.empty()) {
                m_TargetWaypointIndex = 0;
            } else {
                Logger::Log(F("No waypoints available!!!!!!!!!!!!!!!!!!!!!"));
            }
        }

        double m_InIronsAngle; // Angle in degrees that defines when we are in irons
        double m_DistanceToChangeTack;
        double m_AllowedHeadingError = 5.0; // Degrees
        double m_AllowedSailOutError = 1.0; // Percentage, this is the allowed error for the sail out position
        double m_MaxRudderAngle = 45.0; // Degrees, this is the maximum angle the rudder can be at

        int m_TargetWaypointIndex = 0;
        TackingState m_CurrentTack = NotInIrons;

        void virtual Update() override {
            int sailAngle = abs(ElectronicsManager::WindSensor->GetDirection() - 180);
            double desiredSailOut = (int)map(sailAngle, m_InIronsAngle, 180, 0, 100);
            if (m_AllowedSailOutError < abs(ElectronicsManager::WinchServo->GetAngle() - desiredSailOut)) {
                ElectronicsManager::WinchServo->SetAngle(static_cast<int>(desiredSailOut));
            }

            double desiredHeading = DesiredHeading();
            if (desiredHeading != -1) {
                double headingError = fmod(desiredHeading - ElectronicsManager::Magnetometer->GetHeading(), 360);
                double idealRudderAngle = constrain(headingError, -m_MaxRudderAngle, m_MaxRudderAngle);
                double desiredRudderAngle = map(idealRudderAngle, -90, 90, 0, ElectronicsManager::RudderServo->GetRotationRange());

                if (abs(ElectronicsManager::RudderServo->GetAngle() - desiredRudderAngle) > 5) {
                    ElectronicsManager::RudderServo->SetAngle(static_cast<int>(desiredRudderAngle));
                }
            }

            if (WaypointManager::waypoints[m_TargetWaypointIndex].pointIsInRadius(ElectronicsManager::Gps->GetPosition())) {
                Logger::Log(F("Reached waypoint: "), false);
                Logger::Log(String(m_TargetWaypointIndex));
                m_TargetWaypointIndex++;
                if (m_TargetWaypointIndex >= WaypointManager::waypoints.size()) {
                    Logger::Log(F("End of waypoints reached, resetting to first waypoint."));
                    m_TargetWaypointIndex = 0;
                }
            }
        }

        void double DesiredHeading() {
            double waypointCourse = Waypoint::courseTo(ElectronicsManager::Gps->GetPosition(), WaypointManager::waypoints[m_TargetWaypointIndex].m_Position);
            double relativeWindDirection = GetRelativeWindDirection(waypointCourse);
            bool isTackingNeeded = isRelativeWindDirectionInIrons(relativeWindDirection);

            if (!isTackingNeeded) {
                m_CurrentTack = NotInIrons;
                return waypointCourse;
            }

            if (m_CurrentTack != NotInIrons) {
                // We are already tacking, so we need to check if we are still in irons and the distance to the next tack

                double distanceToRestrictedArea = WaypointManager::DistanceToRestrictedArea(ElectronicsManager::Gps->GetPosition(), waypointCourse);

                if (distanceToRestrictedArea != -1) {
                    if (distanceToRestrictedArea > m_DistanceToChangeTack) {
                        // We are still in irons and far enough from the restricted area, so we can continue tacking
                        return -1;
                    }
                    // We are still in irons, but we are too close to the restricted area, so we need to change tack
                    Logger::Log(F("We are still in irons, but we are too close to the restricted area, changing tack."));
                } else {
                    // WE ARE OUTSIDE O NOSE
                    Logger::Log(F("We are outside the sail zone, recalculating course."));
                }
            }

            Logger::Log(F("Recalculating course due to tacking being needed."));

            double starBoardTackCourse = fmod(waypointCourse + abs(m_InIronsAngle - relativeWindDirection), 360);
            double portTackCourse = abs(fmod(waypointCourse - abs(m_InIronsAngle - relativeWindDirection), 360));

            double starBoardTackDistance = WaypointManager::DistanceToRestrictedArea(ElectronicsManager::Gps->GetPosition(), starBoardTackCourse);
            double portTackDistance = WaypointManager::DistanceToRestrictedArea(ElectronicsManager::Gps->GetPosition(), portTackCourse);

            double tackingCourse;

            // Check if outside the sail zone
            if (starBoardTackDistance == -1 || portTackDistance == -1) {
                Logger::Log(F("We are outside the sail zone, picking the best tack course."));
                if (starBoardTackDistance == -1 && portTackDistance == -1) {
                    Logger::Log(F("Both tacks are outside the sail zone, this is catastrophic... picking the tack with the least change in heading"));
                    if (starBoardTackCourse < portTackCourse) {
                        m_CurrentTack = StarboardTack;
                        tackingCourse = starBoardTackCourse;
                    } else {
                        m_CurrentTack = PortTack;
                        tackingCourse = portTackCourse;
                    }
                } else if (starBoardTackDistance == -1) {
                    m_CurrentTack = PortTack;
                    tackingCourse = portTackCourse;
                } else {
                    m_CurrentTack = StarboardTack;
                    tackingCourse = starBoardTackCourse;
                }
            }
            // Is within the sailzone
            else if (starBoardTackDistance > portTackDistance) {
                m_CurrentTack = StarboardTack;
                tackingCourse = starBoardTackCourse;
            } else {
                m_CurrentTack = PortTack;
                tackingCourse = portTackCourse;
            }

            return tackingCourse();
        }

        static double GetRelativeWindDirection(double bearing) {
            return abs(fmod(ElectronicsManager::WindSensor->GetDirection() - bearing, 360));
        }

        bool isRelativeWindDirectionInIrons(double relativeWindDirection) {
            return (relativeWindDirection >= 0 && relativeWindDirection <= m_InIronsAngle) || (relativeWindDirection >= 360 - m_InIronsAngle && relativeWindDirection <= 360);
        }
    };
}
