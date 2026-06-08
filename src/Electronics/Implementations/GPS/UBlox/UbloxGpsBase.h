/// Created by Computery on 10/28/2024.

#pragma once

#include <SparkFun_u-blox_GNSS_v3.h>
#include "Electronics/Types/Gps/GpsBase.h"

namespace Electronics::Types {
    class UbloxGpsBase : public GpsBase {
    public:
        void Update() override;
        GpsFix GetFix() override;
        double GetLatitude() override;
        double GetLongitude() override;
        double GetSpeed() override;
        double GetHeading() override;
        bool IsTimeValid() override;
        bool IsDateValid() override;
        uint16_t GetYear() override;
        uint8_t GetMonth() override;
        uint8_t GetDay() override;
        uint8_t GetHour() override;
        uint8_t GetMinute() override;
        uint8_t GetSecond() override;
        uint16_t GetMillisecond() override;

    protected:
        double m_Speed = 0;
        GpsFix m_Fix = NoFix;
        double m_Latitude = 0;
        double m_Longitude = 0;
        double m_Heading = 0;
        bool m_TimeValid = false;
        bool m_DateValid = false;
        uint16_t m_Year = 0;
        uint8_t m_Month = 0;
        uint8_t m_Day = 0;
        uint8_t m_Hour = 0;
        uint8_t m_Minute = 0;
        uint8_t m_Second = 0;
        uint16_t m_Millisecond = 0;
        SFE_UBLOX_GNSS m_UbloxGnss;
    };
}
