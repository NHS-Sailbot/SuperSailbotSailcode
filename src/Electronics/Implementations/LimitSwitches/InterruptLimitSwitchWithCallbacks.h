/// Created by Computery on 11/6/2024.

#pragma once

#include "Electronics/Types/LimitSwitch/LimitSwitchBase.h"
#include "Logging/Logger.h"

namespace Electronics::Implementations {
    class InterruptLimitSwitchWithCallbacks final : public Types::LimitSwitchBase {
    public:
        explicit InterruptLimitSwitchWithCallbacks(uint8_t limitPin);

        void LimitHit() override;

        // There not a good way to compare callbacks, so we use an index to identify them
        // it's not like we even need to ever deregister them, but we can if we want to
        int RegisterCallback(const std::function<void()>& callback) {
            callbacks.push_back(callback);
            return static_cast<int>(callbacks.size() - 1); // Return the index of the callback
        }

        bool DeregisterCallback(int index) {
            if (index < 0 || index >= static_cast<int>(callbacks.size())) {
                return false;
            }
            callbacks.erase(callbacks.begin() + index); // Remove the callback at the specified index
            return true;
        }
    private:
        std::vector<std::function<void()>> callbacks;
    };
}
