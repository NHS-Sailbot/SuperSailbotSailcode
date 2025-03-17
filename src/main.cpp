/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/ElectronicsManager.h"
#include "Sailing/AutopilotManager.h"
#include "Utilities/LEDStuff.h"
#include "mbed_toolchain.h"

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

// This is so that the system resets if it crashes instead of just blinking the LED over and over again.
MBED_NORETURN void mbed_die () {
    SerialManager::GetSerial().println(F("The boat has crashed!"));
    LEDStuff::SetRGB(true, true, true);
    delay(1000);
    LEDStuff::SetRGB(false, false, false);
    NVIC_SystemReset();
}