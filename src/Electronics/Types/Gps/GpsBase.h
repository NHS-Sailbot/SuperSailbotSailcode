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
        /// Returns the current speed of the GPS, based on the last two updates. Measured in meters per second.
        virtual double GetSpeed() = 0;
        /// Returns the current heading of the GPS, based on the last two updates. Measured in degrees from 0 to 360. 0 is north, 90 is east, 180 is south, 270 is west.
        virtual double GetHeading() = 0;
    };
}
