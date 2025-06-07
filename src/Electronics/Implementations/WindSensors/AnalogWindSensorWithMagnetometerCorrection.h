/// Created by Computery on 11/6/2024.

#pragma once

#include <Arduino.h>
#include "Electronics/Types/Magnetometer/MagnetometerBase.h"
#include "Electronics/Types/WindSensor/WindSensorBase.h"

namespace Electronics::Implementations::WindSensors {
    class AnalogWindSensorWithMagnetometerCorrection final : public Types::WindSensorBase {
    public:
        AnalogWindSensorWithMagnetometerCorrection(uint8_t windSensorPin, Types::MagnetometerBase* magnetometer);
        void Update() override;
        double GetDirection() override;

    private:
        uint8_t m_WindSensorPin;
        double m_WindDirection = 0;
        Types::MagnetometerBase* m_Magnetometer;
    };
}
