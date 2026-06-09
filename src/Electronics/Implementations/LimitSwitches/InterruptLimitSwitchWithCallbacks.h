/// Created by Computery on 11/6/2024.

#pragma once

#include "Constants.h"
#include "Electronics/Types/LimitSwitch/LimitSwitchBase.h"
#include "Logging/Logger.h"

namespace Electronics::Implementations {
    class InterruptLimitSwitchWithCallbacks final : public Types::LimitSwitchBase {
    public:
        explicit InterruptLimitSwitchWithCallbacks(uint8_t limitPin);

        void LimitHit() override;

        // There not a good way to compare callbacks, so we use an index to identify them
        // it's not like we even need to ever deregister them, but we can if we want to
        // Cannot exceed Constants::MAX_LIMIT_SWITCH_CALLBACKS active callbacks; returns -1 when full.
        int RegisterCallback(const std::function<void()>& callback) {
            for (size_t i = 0; i < Constants::MAX_LIMIT_SWITCH_CALLBACKS; ++i) {
                if (m_Callbacks[i].active) {
                    continue;
                }

                m_Callbacks[i].active = true;
                m_Callbacks[i].callback = callback;
                return static_cast<int>(i);
            }

            return -1;
        }

        bool DeregisterCallback(const int index) {
            if (index < 0 || index >= static_cast<int>(Constants::MAX_LIMIT_SWITCH_CALLBACKS)) {
                return false;
            }

            CallbackEntry& entry = m_Callbacks[index];
            if (!entry.active) {
                return false;
            }

            entry.active = false;
            entry.callback = nullptr;
            return true;
        }

    private:
        struct CallbackEntry {
            bool active = false;
            std::function<void()> callback;
        };

        CallbackEntry m_Callbacks[Constants::MAX_LIMIT_SWITCH_CALLBACKS] = {};
    };
}
