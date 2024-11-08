/// Created by Computery on 11/6/2024.

#pragma once

#include "Electronics/Types/LimitSwitch/LimitSwitchBase.h"

namespace Electronics::Implementations {
    class InterruptLimitSwitchMethod final : public Types::LimitSwitchBase {
    public:
        explicit InterruptLimitSwitchMethod(uint8_t limitPin, const std::function<void()> &callback);

        void LimitHit() override;

    private:
        std::function<void()> m_Callback;
    };
}
