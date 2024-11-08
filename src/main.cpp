/// Created by Computery on 9/19/2024.
/// Sailbot 2025, this time around programming wins the competition
/// Team:
///     Lead Programmer: Christoper Rohland (Discord: Computery, GitHub: C0mputery)

#include <Arduino.h>
#include <Logging/Logger.h>

#include "Electronics/ElectronicHandler.h"
#include "FileSystem/FileSystem.h"

using namespace Logging;
using namespace Electronics;

void setup() {
    Logger::Start();
    ElectronicHandler::Start();
    Logger::Log(F("Boat electronics started!"));
}

void loop() {
    ElectronicHandler::Update();
}