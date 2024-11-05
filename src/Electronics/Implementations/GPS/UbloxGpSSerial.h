/// Created by Computery on 10/28/2024.

#ifndef UBLOXGPSSERIAL_H
#define UBLOXGPSSERIAL_H

#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "Electronics/Types/GpsBase.h"
#include "Logging/Logger.h"

using namespace Logging;
using namespace Electronics::Types;

class UbloxGpSSerial : public GpsBase {
public:
    void Init(HardwareSerial& serial) {
        Logger::Log(F("Init GPS..."));
        if (myGNSS.begin(serial, 1000, false) == false) //Connect to the u-blox module using serial port
        {
            Logger::Log(F("u-blox GNSS not detected at default I2C address. Please check wiring."));
        }

        myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR
    }

    GpsFix Update() override {
        Logger::Log(F("Updating GPS..."));

        double latitude = static_cast<double>(myGNSS.getLatitude()) / 10000000.0;
        double longitude = static_cast<double>(myGNSS.getLongitude()) / 10000000.0;

        if (latitude == 0 || longitude == 0) {
            Logger::Log(F("GPS data invalid or unavailable."));
        } else {
            m_Latitude = latitude;
            m_Longitude = longitude;
        }

        m_Fix = myGNSS.getFixType() == 5 ? Fix : NoFix;
        m_Speed = static_cast<double>(myGNSS.getGroundSpeed()) / 1000.0;

        return m_Fix;
    }

    GpsFix GetFix() override {
        return m_Fix;
    }

    double GetLatitude() override {
        return m_Latitude;
    }

    double GetLongitude() override {
        return m_Longitude;
    }

    double GetSpeed() override {
        return m_Speed;
    }

private:
    double m_Speed = 0;
    GpsFix m_Fix = NoFix;
    double m_Latitude = 0;
    double m_Longitude = 0;
    SFE_UBLOX_GNSS myGNSS;
};

#endif