#pragma once

#include <cmath>

#include "Constants.h"

namespace Utilitys {
    class Degrees {
    public:
        /// Normalize to [0, 360).
        static double Wrap360(double degrees) {
            degrees = std::fmod(degrees, Constants::FULL_CIRCLE);
            if (degrees < 0.0) {
                degrees += Constants::FULL_CIRCLE;
            }
            return degrees;
        }

        /// Normalize to (-180, 180].
        static double Wrap180(double degrees) {
            return Wrap360(degrees + 180.0) - 180.0;
        }

        /// Shortest signed rotation from `from` to `to`, in (-180, 180].
        static double Difference(double from, double to) {
            return Wrap180(to - from);
        }

        /// Shortest unsigned separation between two headings, in [0, 180].
        static double AngularDistance(double a, double b) {
            const double diff = Difference(a, b);
            return diff < 0.0 ? -diff : diff;
        }
    };
}
