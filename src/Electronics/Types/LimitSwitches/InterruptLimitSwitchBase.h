/// Created by Computery on 11/6/2024.

#pragma once

#include <Arduino.h>

namespace Electronics::Types {
    class InterruptLimitSwitchBase {
    public:
        virtual ~InterruptLimitSwitchBase() {
            LimitSwitches.erase(std::remove(LimitSwitches.begin(), LimitSwitches.end(), this), LimitSwitches.end());
        }

        inline static std::vector<InterruptLimitSwitchBase*> LimitSwitches = {};

        explicit InterruptLimitSwitchBase(uint8_t limitPin) {
            LimitSwitches.push_back(this);
            m_LimitPin = limitPin;
            pinMode(m_LimitPin, INPUT_PULLUP);
            attachInterrupt(digitalPinToInterrupt(m_LimitPin), staticLimitHit, FALLING);
        }

        static void staticLimitHit() {
            for (InterruptLimitSwitchBase *limitSwitch: LimitSwitches) {
                if (digitalRead(limitSwitch->m_LimitPin) == LOW) {
                    limitSwitch->LimitHit();
                }
            }
        }

        virtual void LimitHit() = 0;

    private:
        uint8_t m_LimitPin;
    };
}
