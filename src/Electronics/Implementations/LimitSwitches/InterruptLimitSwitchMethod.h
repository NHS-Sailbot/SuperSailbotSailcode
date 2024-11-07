/// Created by Computery on 11/6/2024.

#pragma once

#include "Electronics/Types/LimitSwitches/InterruptLimitSwitchBase.h"
#include "Logging/Logger.h"

namespace Electronics::Types {
    class InterruptLimitSwitchMethod final : public InterruptLimitSwitchBase {
    public:
        explicit InterruptLimitSwitchMethod(uint8_t limitPin, const std::function<void()> &callback) : InterruptLimitSwitchBase(limitPin) {
            m_Callback = callback;
        }

        void LimitHit() override {
            if (m_Callback) { m_Callback(); }
            else { Logging::Logger::Log(F("InterruptLimitSwitchMethod callback is null??")); }
        }

    private:
        std::function<void()> m_Callback;
    };
}
