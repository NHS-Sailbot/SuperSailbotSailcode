/// Created by Computery on 9/19/2024.

#pragma once

#include <Servo.h>
#include "Electronics/Types/Servo/ServoBase.h"

namespace Electronics::Implementations::Servos {
    class ArduinoServo final : public Types::ServoBase {
    public:
        explicit ArduinoServo(uint8_t pin, int rotationRange = 180);

        int GetAngle() override;

        void SetAngle(int angle) override;

    private:
        Servo m_Servo;
        int m_Angle = 0;
        int m_RotationRange = 180;
    };
}
