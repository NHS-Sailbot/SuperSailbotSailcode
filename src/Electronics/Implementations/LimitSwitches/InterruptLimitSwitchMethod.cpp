/// Created by Computery on 11/8/2024.

#include "InterruptLimitSwitchMethod.h"
#include "Logging/Logger.h"

using namespace Logging;

namespace Electronics::Implementations {
    InterruptLimitSwitchMethod::InterruptLimitSwitchMethod(uint8_t limitPin, const std::function<void()> &callback): LimitSwitchBase(limitPin) {
        Logger::Log(F("Creating InterruptLimitSwitchMethod..."));
        m_Callback = callback;
        if (!m_Callback) {
            Logger::Log(F("Attempted to create InterruptLimitSwitchMethod with null callback, this is not allowed!"));
            return;
        }
        Logger::Log(F("Interrupt Limit Switch with method created!"));
    }

    void InterruptLimitSwitchMethod::LimitHit() {
        if (m_Callback) { m_Callback(); }
        else { Logger::Log(F("InterruptLimitSwitchMethod callback is null??")); }
    }
}