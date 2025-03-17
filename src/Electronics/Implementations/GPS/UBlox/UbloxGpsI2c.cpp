/// Created by Computery on 11/5/2024.

#include "UbloxGpsI2c.h"
#include "Logging/Logger.h"

using namespace Logging;

namespace Electronics::Implementations::Gps {
    UbloxGpsI2c::UbloxGpsI2c(MbedI2C* i2cWire = &Wire, uint8_t address = 66) {
        Logger::Log(F("Initializing Ublox GPS on I2C..."));

        if (m_UbloxGnss.begin(*i2cWire, address) == false) {
            Logger::Log(F("Ublox GPS not detected. Please check wiring."));
            return;
        }
        m_UbloxGnss.setI2COutput(COM_TYPE_UBX);

        Logger::Log(F("Ublox GPS initialized!"));
    }
}
