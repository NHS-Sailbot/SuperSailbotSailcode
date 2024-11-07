/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)



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
    /*mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    Logger::Log(F("Heap stats:"));
    Logger::Log(F("    Current size: "), false);
    Serial.println(heap_stats.current_size);
    Logger::Log(F("    Max size: "), false);
    Serial.println(heap_stats.max_size);
    Logger::Log(F("    Total size: "), false);
    Serial.println(heap_stats.total_size);
    Logger::Log(F("    Reserved size: "), false);
    Serial.println(heap_stats.reserved_size);
    Logger::Log(F("    Alloc count: "), false);
    Serial.println(heap_stats.alloc_cnt);
    Logger::Log(F("    Alloc fail count: "), false);
    Serial.println(heap_stats.alloc_fail_cnt);
    Logger::Log(F("    Overhead size: "), false);
    Serial.println(heap_stats.overhead_size);*/

    BoatElectronics::Update();
}