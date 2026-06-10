// Created by sailbot on 6/10/25.

#pragma once

#include <Arduino.h>

#include "Electronics/Implementations/LimitSwitches/InterruptLimitSwitchWithCallbacks.h"
#include "Electronics/Implementations/Winches/ServoWinch.h"

namespace Electronics::Implementations::Winches {
    class LimitSwitchCalibratedServoWinch final : public ServoWinch {
    public:
        LimitSwitchCalibratedServoWinch(Types::ServoBase& servo, InterruptLimitSwitchWithCallbacks& fullInLimitSwitch,
                InterruptLimitSwitchWithCallbacks& fullOutLimitSwitch, int initialFullOutAngle, int initialFullInAngle)
                : ServoWinch(servo, initialFullOutAngle, initialFullInAngle) {
            RunToFullIn(fullInLimitSwitch);
            RunToFullOut(fullOutLimitSwitch);
            SetLetOutPercentage(0.0);
        }

    private:
        static constexpr int kCreepStep = 10;
        static constexpr int kCreepDelayMs = 25;
        static constexpr int kMaxCreepSteps = 500;

        static int StepToward(int target, int from) {
            return target > from ? kCreepStep : -kCreepStep;
        }

        void RunToFullIn(InterruptLimitSwitchWithCallbacks& limitSwitch) {
            bool limitHit = limitSwitch.IsPressed();
            const int callbackIndex = limitSwitch.RegisterCallback([&]() { limitHit = true; });

            int angle = GetAngle();
            const int step = StepToward(m_FullInAngle, m_FullOutAngle);
            for (int i = 0; i < kMaxCreepSteps && !limitHit; ++i) {
                angle += step;
                m_Servo.SetAngle(angle);
                delay(kCreepDelayMs);
            }

            m_FullInAngle = angle;
            SetLetOutPercentage(0.0);
            limitSwitch.DeregisterCallback(callbackIndex);
        }

        void RunToFullOut(InterruptLimitSwitchWithCallbacks& limitSwitch) {
            bool limitHit = limitSwitch.IsPressed();
            const int callbackIndex = limitSwitch.RegisterCallback([&]() { limitHit = true; });

            int angle = GetAngle();
            const int step = StepToward(m_FullOutAngle, m_FullInAngle);
            for (int i = 0; i < kMaxCreepSteps && !limitHit; ++i) {
                angle += step;
                m_Servo.SetAngle(angle);
                delay(kCreepDelayMs);
            }

            m_FullOutAngle = angle;
            SetLetOutPercentage(100.0);
            limitSwitch.DeregisterCallback(callbackIndex);
        }
    };
}
