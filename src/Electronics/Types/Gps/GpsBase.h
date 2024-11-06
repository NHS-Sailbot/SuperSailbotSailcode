#pragma once

namespace Electronics::Types {
    enum GpsFix {
        DeadReckoning,
        NoFix,
        Fix,
    };

    class GpsBase {
    public:
        virtual ~GpsBase() = default;

        /// Gets called once per updated, makes the GPS update its cached data.
        virtual GpsFix Update() = 0;

        /// Returns the cached fix status of the GPS.
        virtual GpsFix GetFix() = 0;

        /// Returns the cached latitude of the GPS.
        virtual double GetLatitude() = 0;

        /// Returns the cached longitude of the GPS.
        virtual double GetLongitude() = 0;

        /// Returns the current speed of the GPS, based on the last two updates.
        virtual double GetSpeed() = 0;
    };
}
