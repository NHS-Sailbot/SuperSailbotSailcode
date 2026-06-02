// Created by sailbot on 6/10/25.

#pragma once

#include <Arduino.h>
#include "Electronics/Types/Servo/ServoBase.h"
#include "Electronics/Types/Winch/WinchBase.h"

namespace Electronics::Implementations::Winches {
    class ServoWinch final : public Types::WinchBase {
    public:
        ServoWinch(Types::ServoBase& servo, int fullOutAngle, int fullInAngle)
            : m_Servo(servo),
              m_FullOutAngle(fullOutAngle),
              m_FullInAngle(fullInAngle) {}

        double GetLetOutPercentage() override {
            return m_LetOutPercentage;
        }

        void SetLetOutPercentage(double percent) override {
            m_LetOutPercentage = constrain(percent, 0.0, 100.0);
            const int angle = static_cast<int>(m_FullInAngle + (m_LetOutPercentage / 100.0) * (m_FullOutAngle - m_FullInAngle));
            m_Servo.SetAngle(angle);
        }

    private:
        Types::ServoBase& m_Servo;
        int m_FullOutAngle;
        int m_FullInAngle;
        double m_LetOutPercentage = 0.0;
    };
}
