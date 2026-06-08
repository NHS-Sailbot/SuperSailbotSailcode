#pragma once
#include <cstdint>
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
        /// Returns the current speed of the GPS. Measured in meters per second.
        virtual double GetSpeed() = 0;
        /// Returns the current heading of the GPS. Measured in degrees from 0 to 360. 0 is north, 90 is east, 180 is south, 270 is west.
        virtual double GetHeading() = 0;

        /// Returns whether the cached GPS UTC time-of-day is valid.
        virtual bool IsTimeValid() = 0;
        /// Returns whether the cached GPS UTC calendar date is valid.
        virtual bool IsDateValid() = 0;
        /// Returns the cached UTC year.
        virtual uint16_t GetYear() = 0;
        /// Returns the cached UTC month (1-12).
        virtual uint8_t GetMonth() = 0;
        /// Returns the cached UTC day (1-31).
        virtual uint8_t GetDay() = 0;
        /// Returns the cached UTC hour (0-23).
        virtual uint8_t GetHour() = 0;
        /// Returns the cached UTC minute (0-59).
        virtual uint8_t GetMinute() = 0;
        /// Returns the cached UTC second (0-60).
        virtual uint8_t GetSecond() = 0;
        /// Returns the cached UTC millisecond (0-999).
        virtual uint16_t GetMillisecond() = 0;
        /// Returns the lat and long as a point2d
        virtual Utilitys::Point2D GetPosition() {
            return { GetLatitude(), GetLongitude() };
        }
    };
}
