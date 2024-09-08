#include <Arduino.h>
#include <Logging/Logger.h>

using namespace Logging;

void setup() {
    Logger::Begin(&Serial, 115200);
}

// the loop function runs over and over again forever
void loop() {
    Logger::Println(F("Hello, world!"));
    delay(1000);
}
