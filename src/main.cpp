/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/ElectronicsManager.h"
#include "Sailing/AutopilotManager.h"

using namespace Logging;
using namespace Electronics;
using namespace Sailing;

void setup() {
    SerialManager::Start();
    ElectronicsManager::Start();
    AutopilotManager::Start();
}

void loop() {
    SerialManager::Update();
    ElectronicsManager::Update();
    AutopilotManager::Update();
}