/// Created by Computery on 11/8/2024.

#include "InterruptLimitSwitchMethod.h"
#include "Logging/Logger.h"

Electronics::Implementations::InterruptLimitSwitchMethod::InterruptLimitSwitchMethod(uint8_t limitPin,
    const std::function<void()> &callback): LimitSwitchBase(limitPin) {
    m_Callback = callback;
}

void Electronics::Implementations::InterruptLimitSwitchMethod::LimitHit() {
    if (m_Callback) { m_Callback(); }
    else { Logging::Logger::Log(F("InterruptLimitSwitchMethod callback is null??")); }
}
