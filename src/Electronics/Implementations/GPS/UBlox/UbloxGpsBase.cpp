/// Created by Computery on 11/5/2024.

#include "UbloxGpsBase.h"
#include <Logging/Logger.h>

#include "Utilities/LEDStuff.h"

using namespace Logging;
using namespace Electronics::Types;

void UbloxGpsBase::Update() {
    if (!m_UbloxGnss.getPVT()){
        return; // No data available
    }
    
    // 0=no fix, 1=dead reckoning, 2=2D, 3=3D, 4=GNSS, 5=Time fix
    const uint8_t fixType = m_UbloxGnss.getFixType();
    
    if (fixType == 0 || fixType == 5) {
        m_Fix = NoFix;
    } else if (fixType == 1) {
        m_Fix = DeadReckoning;
    } else {
        m_Fix = Fix;
    }

    if (m_Fix == NoFix) {
        return;
    }

    LEDStuff::SetRGB(true, false, false);

    const double latitude = static_cast<double>(m_UbloxGnss.getLatitude()) / 10000000.0;
    const double longitude = static_cast<double>(m_UbloxGnss.getLongitude()) / 10000000.0;

    LEDStuff::SetRGB(false, false, true);
    
    if (latitude == 0 || longitude == 0) {
        Logger::Log(F("GPS data invalid or unavailable... keeping old data."));
        return;
    }

    m_Latitude = latitude;
    m_Longitude = longitude;
    m_Speed = static_cast<double>(m_UbloxGnss.getGroundSpeed()) / 1000.0;
    m_Heading = static_cast<double>(m_UbloxGnss.getHeading()) / 100000.0;
    
    LEDStuff::SetRGB(false, false, false);
}

GpsFix UbloxGpsBase::GetFix() {
    return m_Fix;
}

double UbloxGpsBase::GetLatitude()  {
    return m_Latitude;
}

double UbloxGpsBase::GetLongitude()  {
    return m_Longitude;
}

double UbloxGpsBase::GetSpeed() {
    return m_Speed;
}

double UbloxGpsBase::GetHeading() {
    return m_Heading;
}


