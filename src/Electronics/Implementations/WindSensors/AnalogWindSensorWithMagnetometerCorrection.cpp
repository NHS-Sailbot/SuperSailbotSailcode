/// Created by Computery on 11/6/2024.

#include "AnalogWindSensorWithMagnetometerCorrection.h"
namespace Electronics::Implementations::WindSensors {
    AnalogWindSensorWithMagnetometerCorrection::AnalogWindSensorWithMagnetometerCorrection(uint8_t windSensorPin, Types::MagnetometerBase *magnetometer) {
        m_WindSensorPin = windSensorPin;
        pinMode(m_WindSensorPin, INPUT);
        m_Magnetometer = magnetometer;
    }

    void AnalogWindSensorWithMagnetometerCorrection::Update() {
        int analogWindDirection = analogRead(m_WindSensorPin);
        double windDirectionRelative = map(analogWindDirection, 0, 1023, 0, 359);
        windDirectionRelative += m_Magnetometer->GetHeading();
        windDirectionRelative = fmod(windDirectionRelative, 360);
        m_WindDirection = windDirectionRelative;
    }

    double AnalogWindSensorWithMagnetometerCorrection::GetWindDirection() {
        return m_WindDirection;
    }
}
