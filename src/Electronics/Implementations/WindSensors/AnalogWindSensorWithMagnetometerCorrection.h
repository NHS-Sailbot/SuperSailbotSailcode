/// Created by Computery on 11/6/2024.

#pragma once
#include "Electronics/Types/WindSensorBase.h"
#include <Arduino.h>

#include "Electronics/Types/Magnetometer/MagnetometerBase.h"

namespace Electronics::Implementations::WindSensors {
    class AnalogWindSensorWithMagnetometerCorrection : public Types::WindSensorBase {
    public:
        AnalogWindSensorWithMagnetometerCorrection(uint8_t windSensorPin, Types::MagnetometerBase *magnetometer) {
            m_WindSensorPin = windSensorPin;
            pinMode(m_WindSensorPin, INPUT);
            m_Magnetometer = magnetometer;
        }

        void Update() override {
            int analogWindDirection = analogRead(m_WindSensorPin);
            double windDirectionRelative = map(analogWindDirection, 0, 1023, 0, 359);
            windDirectionRelative += m_Magnetometer->GetHeading();
            windDirectionRelative = fmod(windDirectionRelative, 360);
            m_WindDirection = windDirectionRelative;
        }

        double GetWindDirection() override {
            return m_WindDirection;
        }
    private:
        uint8_t m_WindSensorPin;
        double m_WindDirection = 0;
        Types::MagnetometerBase *m_Magnetometer;
    };
}
