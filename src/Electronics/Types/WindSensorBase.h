/// Created by Computery on 11/6/2024.

#pragma once

namespace Electronics::Types {
    class WindSensorBase {
        public:
            virtual ~WindSensorBase() = default;

            /// Updates the wind sensor
            virtual void Update() = 0;

            /// Returns the wind direction in degrees, 0 is north, 90 is east, 180 is south, 270 is west
            virtual double GetWindDirection() = 0;
    };
}
