/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

using namespace Logging;

/// Arduino setup function, is called once when the program starts
void setup() {
    Logger::Begin(&Serial, 115200);
}

/// Arduino loop function, is called repeatedly
void loop() {
}