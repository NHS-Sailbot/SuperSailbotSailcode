#pragma once

#include "UtcTime.h"
#include <functional>

namespace Electronics::Types {
    class TimekeepingBase {
    public:
        virtual ~TimekeepingBase() = default;

        virtual void Update() = 0;

        /// True when GPS-backed UTC is available for scheduling and queries.
        virtual bool HasValidUtc() const = 0;

        /// Returns interpolated UTC. Only meaningful when HasValidUtc() is true.
        virtual UtcTime GetCurrentUtc() const = 0;

        /// Fires the callback once after delayMs milliseconds.
        virtual int RegisterDelayCallback(const std::function<void()>& callback, unsigned long delayMs) = 0;

        /// Fires the callback once when UTC reaches target.
        virtual int RegisterTimeCallback(const std::function<void()>& callback, UtcTime target) = 0;

        virtual bool DeregisterCallback(int id) = 0;
    };
}
