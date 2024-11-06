/// Created by Computery on 11/6/2024.

#pragma once

namespace Electronics::Types {
    enum MagnetometerCalibrationStatus {
        NotCalibrated,
        Calibrated,
    };

    struct MagnetometerCalibration {
        MagnetometerCalibrationStatus System;
        MagnetometerCalibrationStatus Gyro;
        MagnetometerCalibrationStatus Accel;
        MagnetometerCalibrationStatus Mag;
    };

    class MagnetometerBase {
        public:
            virtual ~MagnetometerBase() = default;

            /// Returns the heading of the boat in degrees, 0 is north, 90 is east, 180 is south, 270 is west
            virtual double GetHeading() = 0;

            /// Returns the calibration status of the magnetometer
            virtual MagnetometerCalibration GetCalibration() = 0;

            /// Updates the calibration of the magnetometer
            virtual MagnetometerCalibration Update() = 0;
    };
}