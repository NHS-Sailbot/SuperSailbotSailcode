/// Created by Computery on 6/1/2026.

#pragma once

namespace Electronics::Types {
    class WinchBase {
    public:
        virtual ~WinchBase() = default;

        /// How much the sail has been let out, 0-100.
        virtual double GetLetOutPercentage() = 0;

        /// Lets the sail out or pulls it in. Zero to a hundred.
        virtual void SetLetOutPercentage(double percent) = 0;
    };
}
