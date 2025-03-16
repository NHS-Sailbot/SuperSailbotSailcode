/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/ElectronicsManager.h"
#include "Sailing/AutopilotManager.h"
#include "Utilities/LEDStuff.h"

using namespace Logging;
using namespace Electronics;
using namespace Sailing;

void setup() {
    SerialManager::Start();
    ElectronicsManager::Start();
    AutopilotManager::Start();
}

void loop() {
    //LEDStuff::SetRGB(true, false, false); // Set LED to red
    SerialManager::Update();
    //LEDStuff::SetRGB(false, true, false); // Set LED to green
    ElectronicsManager::Update();
    //LEDStuff::SetRGB(false, false, true); // Set LED to blue
    AutopilotManager::Update();
}