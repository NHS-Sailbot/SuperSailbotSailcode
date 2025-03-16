/// Created by Computery on 11/8/2024.

#include "InterruptLimitSwitchWithCallbacks.h"
#include "Logging/Logger.h"

using namespace Logging;

namespace Electronics::Implementations {
    InterruptLimitSwitchWithCallbacks::InterruptLimitSwitchWithCallbacks(uint8_t limitPin): LimitSwitchBase(limitPin) {
        Logger::Log(F("Creating InterruptLimitSwitchMethod..."));
        Logger::Log(F("Interrupt Limit Switch with method created!"));
    }

    void InterruptLimitSwitchWithCallbacks::LimitHit() {
        for (auto& callback : callbacks) { callback(); }
    }
}