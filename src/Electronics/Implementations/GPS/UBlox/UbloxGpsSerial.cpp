/// Created by Computery on 11/5/2024.

#include "UbloxGpsSerial.h"
#include "Logging/Logger.h"

using namespace Logging;

namespace Electronics::Implementations::Gps {
    UbloxGpsSerial::UbloxGpsSerial(HardwareSerial* serialPort = &Serial1) {
        Logger::Log(F("Initializing Ublox GPS on Serial..."));

        if (m_UbloxGnss.begin(*serialPort) == false){
            Logger::Log(F("Ublox GPS not detected. Please check wiring."));
            return;
        }
        m_UbloxGnss.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);

        Logger::Log(F("Ublox GPS initialized!"));
    }
}