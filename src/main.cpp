/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

// The Ublox Library breaks if the following includes are not included
#include <Wire.h>
#include <SPI.h>

using namespace Logging;

void setup() {
    Logger::Begin(&Serial, 115200);
    Logger::Log(F("Hello, World!"));
}

void loop() {
}