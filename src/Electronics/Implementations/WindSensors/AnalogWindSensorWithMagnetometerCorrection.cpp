/// Created by Computery on 11/6/2024.

#include "AnalogWindSensorWithMagnetometerCorrection.h"

#include "Electronics/ElectronicsManager.h"
#include "Utilities/Degrees.h"
#include "Utilities/Math.h"

namespace Electronics::Implementations::WindSensors {
    AnalogWindSensorWithMagnetometerCorrection::AnalogWindSensorWithMagnetometerCorrection(uint8_t windSensorPin) {
        m_WindSensorPin = windSensorPin;
        pinMode(m_WindSensorPin, INPUT);
    }

    void AnalogWindSensorWithMagnetometerCorrection::Update() {
        const int analogWindDirection = analogRead(m_WindSensorPin);
        double windDirectionRelative = Utilitys::Math::Remap(analogWindDirection, 0.0, 1023.0, 0.0, 360.0);
        windDirectionRelative += ElectronicsManager::Magnetometer->GetHeading();
        windDirectionRelative = Utilitys::Degrees::Wrap360(windDirectionRelative);
        m_WindDirection = windDirectionRelative;
    }

    double AnalogWindSensorWithMagnetometerCorrection::GetDirection() {
        return m_WindDirection;
    }
}
