/// Created by Computery on 9/19/2024.

#pragma once

#include <Servo.h>
#include <Arduino.h>
#include "Electronics/Types/ServoBase.h"

namespace Electronics::Implementations::Servos {
    class ArduinoServo final : public Types::ServoBase {
    public:
        explicit ArduinoServo(const uint8_t pin, const int rotationRange = 180) {
            m_Servo.attach(pin);
            m_RotationRange = rotationRange;
        }
        int GetAngle() override {
            return m_Angle;
        }
        void SetAngle(int angle) override {
            angle = map(angle, 0, 180, 0, m_RotationRange);
            m_Angle = angle;
        }
    private:
        Servo m_Servo;
        int m_Angle = 0;
        int m_RotationRange = 180;
    };
}
