/// Created by Computery on 11/8/2024.

#include "ArduinoServo.h"
#include <Arduino.h>

#include "Logging/Logger.h"

namespace Electronics::Implementations {
    Servos::ArduinoServo::ArduinoServo(const uint8_t pin, const int rotationRange) {
        Logging::Logger::Log(F("Initializing Arduino servo..."));
        m_Servo.attach(pin);
        m_RotationRange = rotationRange;
        Logging::Logger::Log(F("Arduino servo initialized!"));
    }

    int Servos::ArduinoServo::GetAngle() {
        return m_Angle;
    }

    void Servos::ArduinoServo::SetAngle(int angle) {
        angle = map(angle, 0, 180, 0, m_RotationRange);
        m_Angle = angle;
    }
}
