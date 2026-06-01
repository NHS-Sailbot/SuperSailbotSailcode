#pragma once

namespace Utilitys {
    class Math {
    public:
        /// Linear map from [inMin, inMax] to [outMin, outMax]. Returns outMin if the input range is zero.
        static double Remap(double value, double inMin, double inMax, double outMin, double outMax) {
            if (inMax == inMin) { return outMin; }
            return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
        }

        /// Like Remap, but clamps value to [inMin, inMax] before scaling.
        static double RemapClamped(double value, double inMin, double inMax, double outMin, double outMax) {
            if (value <= inMin) { return outMin; }
            if (value >= inMax) { return outMax; }
            return Remap(value, inMin, inMax, outMin, outMax);
        }
    };
}
