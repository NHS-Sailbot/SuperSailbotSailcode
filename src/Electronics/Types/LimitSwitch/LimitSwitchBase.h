/// Created by Computery on 11/6/2024.

#pragma once

#include <Arduino.h>

namespace Electronics::Types {
    class LimitSwitchBase {
    public:
        virtual ~LimitSwitchBase();

        explicit LimitSwitchBase(uint8_t limitPin);

        /// Called when the limit switch is hit.
        virtual void LimitHit() = 0;

        /// Returns true when the switch is pressed (pin LOW with INPUT_PULLUP).
        bool IsPressed() const;

        /// Returns true when the switch is open / not pressed (pin HIGH with INPUT_PULLUP).
        bool IsOpen() const;

    private:
        inline static std::vector<LimitSwitchBase*> LimitSwitches = {};
        static void staticLimitHit();

        uint8_t m_LimitPin;
        /// Last pin level seen in staticLimitHit (HIGH = open, LOW = pressed with INPUT_PULLUP)
        int m_LastPinState = HIGH;
    };
}
