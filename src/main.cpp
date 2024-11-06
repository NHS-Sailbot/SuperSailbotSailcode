/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/BoatElectronics.h"

using namespace Logging;

void setup() {
    Logger::Start(&Serial, 115200);
    Electronics::BoatElectronics::Start();
}

void loop() {
}