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

    private:
        inline static std::vector<LimitSwitchBase*> LimitSwitches = {};
        static void staticLimitHit();

        uint8_t m_LimitPin;
    };
}
