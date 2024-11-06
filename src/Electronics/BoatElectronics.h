/// Created by Computery on 9/19/2024.

#pragma once

#include "Implementations/GPS/UBlox/UbloxGpsI2c.h"
#include "Types/Gps/GpsBase.h"
#include "Logging/Logger.h"
#include <Wire.h>

using namespace Logging;
using namespace Electronics::Types;

namespace Electronics {
    class BoatElectronics {
    public:
        inline static GpsBase *Gps = nullptr;

        static void Start(MbedI2C* wire = &Wire) {
            Logger::Log(F("Starting electronics..."));
            wire->begin();
            Gps = new Implementations::Gps::UbloxGpsI2c(wire, 66);
        }
    };
}
