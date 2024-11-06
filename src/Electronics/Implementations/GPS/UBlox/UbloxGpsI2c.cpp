/// Created by Computery on 11/5/2024.

#include "UbloxGpsI2c.h"
#include "Logging/Logger.h"

namespace Electronics::Implementations::Gps {
    UbloxGpsI2c::UbloxGpsI2c(MbedI2C* i2cWire = &Wire, uint8_t address = 66) {
        Logging::Logger::Log(F("Init GPS..."));
        if (UbloxGnss.begin(*i2cWire, address) == false) //Connect to the u-blox module using Wire port
        {
            Logging::Logger::Log(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
        }
        UbloxGnss.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
        UbloxGnss.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR
    }
}
