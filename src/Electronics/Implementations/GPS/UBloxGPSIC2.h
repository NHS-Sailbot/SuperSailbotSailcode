/// Created by Computery on 10/21/2024.

#ifndef UBLOXGPSIC2_H
#define UBLOXGPSIC2_H

#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "Electronics/Types/GpsBase.h"
#include "Logging/Logger.h"

using namespace Logging;
using namespace Electronics::Types;

class UBloxGPSI2C : GpsBase {
public:
    void Init() {
        Logger::Log(F("Init GPS..."));
        Wire.begin();
        if (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
        {
            Logger::Log(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
        }

        myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
        myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR
    }

    GpsFix Update() override {
        Logger::Log(F("Updating GPS..."));
        m_Latitude = static_cast<double>(myGNSS.getLatitude()) / 10000000.0;
        m_Longitude = static_cast<double>(myGNSS.getLongitude()) / 10000000.0;
        m_Fix = myGNSS.getFixType() == 5 ? Fix : NoFix;
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
        return static_cast<double>(myGNSS.getGroundSpeed()) / 1000.0;
    }

private:
    GpsFix m_Fix = NoFix;
    double m_Latitude = 0;
    double m_Longitude = 0;
    SFE_UBLOX_GNSS myGNSS;
};


#endif