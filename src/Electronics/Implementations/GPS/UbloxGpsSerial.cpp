/// Created by Computery on 11/5/2024.

#include "UbloxGpsSerial.h"
#include "Logging/Logger.h"

namespace Electronics::Implementations::Gps {
    UbloxGpsSerial::UbloxGpsSerial(HardwareSerial* serialPort = &Serial1) {
        Logging::Logger::Log(F("Init GPS..."));
        if (m_UbloxGnss.begin(*serialPort) == false) //Connect to the u-blox module using Wire port
        {
            Logging::Logger::Log(F("u-blox GNSS not detected at default I2C address. Please check wiring.."));
        }
        m_UbloxGnss.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR
    }
}