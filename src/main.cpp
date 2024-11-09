/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/ElectronicsManager.h"
#include "Sailing/Autopilot/AutopilotManager.h"

using namespace Logging;
using namespace Electronics;
using namespace Autopilot;

void setup() {
    Logger::Start();
    ElectronicsManager::Start();
    Autopilot::AutopilotManager::Start();
}

void loop() {
    ElectronicsManager::Update();
    Autopilot::AutopilotManager::Update();
}