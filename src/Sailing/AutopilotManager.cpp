/// Created by Computery on 11/8/2024.

#include "AutopilotManager.h"

#include "Implementations/StationKeeping.h"
#include "Implementations/PrecisionAutopilot.h"


namespace Sailing {
    // TODO: Utilize the API to dynamically set the autopilot used on startup.
    void AutopilotManager::Start() {
        m_Autopilot = new Implementations::PrecisionAutopilot (
            45.0, // inIronsAngle
            15.0, // distanceToChangeTack
            5.0,  // allowedHeadingError
            1.0,  // allowedSailOutError
            45.0  // maxRudderAngle
        );
        /*
        m_Autopilot = new Implementations::StationKeeping (
            45.0, // inIronsAngle
            15.0, // distanceToChangeTack
            5.0,  // allowedHeadingError
            1.0,  // allowedSailOutError
            45.0  // maxRudderAngle
        );
        static_cast<Implementations::StationKeeping*>(m_Autopilot)->HoldAtWaypoint0ForMinutes(4);
        */
    }

    void AutopilotManager::Update() {
        m_Autopilot->Update();
    }
}
