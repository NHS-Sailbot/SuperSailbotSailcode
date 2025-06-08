/// Created by Computery on 11/8/2024.

#include "AutopilotManager.h"

#include "Implementations/PrecisionAutopilot.h"

namespace Sailing {
    void AutopilotManager::Start() {
        m_Autopilot = new Implementations::PrecisionAutopilot;
    }

    void AutopilotManager::Update() {
        m_Autopilot->Update();
    }
}
