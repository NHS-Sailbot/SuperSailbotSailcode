#pragma once
#include "Utilities/Point2D.h"

namespace Electronics::Types {
    enum GpsFix {
        DeadReckoning = 0,
        NoFix = 1,
        Fix = 2,
    };

    class GpsBase {
    public:
        virtual ~GpsBase() = default;

        /// Gets and caches the latest GPS data.
        virtual void Update() = 0;
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
        // Returns the lat and long as a point2d
        virtual Utilitys::Point2D GetPosition() {
            return { GetLatitude(), GetLongitude() };
        }
    };
}
