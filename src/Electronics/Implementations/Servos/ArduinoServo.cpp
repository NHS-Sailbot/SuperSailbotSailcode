/// Created by Computery on 11/8/2024.

#include "ArduinoServo.h"
#include <Arduino.h>

Electronics::Implementations::Servos::ArduinoServo::ArduinoServo(const uint8_t pin, const int rotationRange) {
    m_Servo.attach(pin);
    m_RotationRange = rotationRange;
}

int Electronics::Implementations::Servos::ArduinoServo::GetAngle() {
    return m_Angle;
}

void Electronics::Implementations::Servos::ArduinoServo::SetAngle(int angle) {
    angle = map(angle, 0, 180, 0, m_RotationRange);
    m_Angle = angle;
}
