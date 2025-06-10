// Created by sailbot on 6/10/25.
// This entire thing is a hack lolz, ideally you just make a winch peripheral

#pragma once

#include <Arduino.h>
#include "ArduinoServo.h"

namespace Electronics::Implementations::Servos{
    class WinchServo final : public ArduinoServo {
    public:
        WinchServo(const uint8_t& pin, int rotationRange, int fullOutAngle, int fullInAngle) : ArduinoServo(pin, rotationRange) {
            m_FullOutAngle = fullOutAngle;
            m_FullInAngle = fullInAngle;
        }

        int m_FullOutAngle; // Angle when the sail is fully out
        int m_FullInAngle; // Angle when the sail is fully in

        void SetAngle(int letOutPercentage) override {
            int angle = map(letOutPercentage, 0, 100, m_FullInAngle, m_FullOutAngle);
            ArduinoServo::SetAngle(angle);
        }
    };
}
