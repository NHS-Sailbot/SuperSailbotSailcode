/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)
///     YALL NEED TO ADD YOUR NAMES



#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/BoatElectronics.h"

using namespace Logging;
using namespace Electronics;

void setup() {
    Logger::Start(&Serial, 115200);
    BoatElectronics::Start();
    Logger::Log(F("Boat electronics started!"));
}

void loop() {
    BoatElectronics::Update();
}