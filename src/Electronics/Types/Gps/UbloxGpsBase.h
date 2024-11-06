/// Created by Computery on 10/28/2024.

#pragma once

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "GpsBase.h"

namespace Electronics::Types {
    class UbloxGpsBase : public GpsBase {
    public:
        GpsFix Update() override;
        GpsFix GetFix() override;
        double GetLatitude() override;
        double GetLongitude() override;
        double GetSpeed() override;
        double GetHeading() override;

    protected:
        double m_Speed = 0;
        GpsFix m_Fix = NoFix;
        double m_Latitude = 0;
        double m_Longitude = 0;
        double m_Heading = 0;
        SFE_UBLOX_GNSS m_UbloxGnss;
    };
}