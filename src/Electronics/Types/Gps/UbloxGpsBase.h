/// Created by Computery on 10/28/2024.

#pragma once

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <Logging/Logger.h>
#include "GpsBase.h"

using namespace Logging;
using namespace Electronics::Types;

class UbloxGpsBase : public GpsBase {
public:
    GpsFix Update() override {
        Logger::Log(F("Updating GPS..."));

        // 0=no fix, 1=dead reckoning, 2=2D, 3=3D, 4=GNSS, 5=Time fix
        const uint8_t fixType = UbloxGnss.getFixType();
        if (fixType == 0 || fixType == 5) {
            m_Fix = NoFix;
        } else if (fixType == 1) {
            m_Fix = DeadReckoning;
        } else {
            m_Fix = Fix;
        }

        if (m_Fix == NoFix) {
            Logger::Log(F("GPS data invalid or unavailable... keeping old data."));
            return m_Fix;
        }

        const double latitude = static_cast<double>(UbloxGnss.getLatitude()) / 10000000.0;
        const double longitude = static_cast<double>(UbloxGnss.getLongitude()) / 10000000.0;

        if (latitude == 0 || longitude == 0) {
            Logger::Log(F("GPS data invalid or unavailable... keeping old data."));
            return m_Fix;
        } else {
            m_Latitude = latitude;
            m_Longitude = longitude;
        }

        m_Speed = static_cast<double>(UbloxGnss.getGroundSpeed()) / 1000.0;

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
    SFE_UBLOX_GNSS UbloxGnss;
};
