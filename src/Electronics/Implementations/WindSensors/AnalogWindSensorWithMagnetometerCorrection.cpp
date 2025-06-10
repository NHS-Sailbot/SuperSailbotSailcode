/// Created by Computery on 11/6/2024.

#include "AnalogWindSensorWithMagnetometerCorrection.h"

#include "Electronics/ElectronicsManager.h"

namespace Electronics::Implementations::WindSensors {
    AnalogWindSensorWithMagnetometerCorrection::AnalogWindSensorWithMagnetometerCorrection(uint8_t windSensorPin) {
        m_WindSensorPin = windSensorPin;
        pinMode(m_WindSensorPin, INPUT);
    }

    void AnalogWindSensorWithMagnetometerCorrection::Update() {
        int analogWindDirection = analogRead(m_WindSensorPin);
        double windDirectionRelative = map(analogWindDirection, 0, 1023, 0, 359);
        windDirectionRelative += ElectronicsManager::Magnetometer->GetHeading();
        windDirectionRelative = fmod(windDirectionRelative, 360);
        m_WindDirection = windDirectionRelative;
    }

    double AnalogWindSensorWithMagnetometerCorrection::GetDirection() {
        return m_WindDirection;
    }
}
