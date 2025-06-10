/// Created by Computery on 9/19/2024.

#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "Electronics/Types/Servo/ServoBase.h"

namespace Electronics::Implementations::Servos {
    class ArduinoServo : public Types::ServoBase {
    public:
        explicit ArduinoServo(uint8_t pin, int rotationRange = 180);

        int GetAngle() override;

        virtual void SetAngle(int angle) override;

        double GetRotationRange() override { return m_RotationRange; }

    private:
        Servo m_Servo;
        int m_Angle = 0;
        int m_RotationRange = 180;
    };
}
