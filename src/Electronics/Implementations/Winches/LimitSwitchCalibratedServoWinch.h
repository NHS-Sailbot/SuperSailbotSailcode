// Created by sailbot on 6/10/25.

#pragma once

#include "Electronics/Implementations/LimitSwitches/InterruptLimitSwitchWithCallbacks.h"
#include "Electronics/Implementations/Winches/ServoWinch.h"

namespace Electronics::Implementations::Winches {
    class LimitSwitchCalibratedServoWinch final : public ServoWinch {
    public:
        LimitSwitchCalibratedServoWinch(
            Types::ServoBase& servo,
            InterruptLimitSwitchWithCallbacks& fullInLimitSwitch,
            InterruptLimitSwitchWithCallbacks& fullOutLimitSwitch,
            int initialFullOutAngle,
            int initialFullInAngle)
            : ServoWinch(servo, initialFullOutAngle, initialFullInAngle) {
            fullInLimitSwitch.RegisterCallback([this]() { OnFullInLimitHit(); });
            fullOutLimitSwitch.RegisterCallback([this]() { OnFullOutLimitHit(); });
            SetLetOutPercentage(0.0);
        }

    private:
        void OnFullInLimitHit() {
            m_FullInAngle = GetAngle();
            m_LetOutPercentage = 0.0;
        }

        void OnFullOutLimitHit() {
            m_FullOutAngle = GetAngle();
            m_LetOutPercentage = 100.0;
        }
    };
}
