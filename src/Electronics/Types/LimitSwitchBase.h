/// Created by Computery on 11/6/2024.

#pragma once

namespace Electronics::Types {
    class LimitSwitchBase {
    public:
        virtual ~LimitSwitchBase() = default;

        /// Updates the limit switch
        virtual void Update() = 0;

        /// Returns true if the limit switch is hit
        virtual bool IsHit() = 0;
    };
}

