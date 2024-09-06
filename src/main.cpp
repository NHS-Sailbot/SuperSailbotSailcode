#include <Arduino.h>
#include <Logging/Logger.h>

using namespace Logging;

void setup() {
    Logger::SetupLogging(&Serial);
}

void loop() {
    Logger::PrintLine(F("Hello, world!"));
    Serial.println(F("Hello, world!"));
}