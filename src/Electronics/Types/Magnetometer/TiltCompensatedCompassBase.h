/// Created by Computery on 11/6/2024.

#pragma once

#include "MagnetometerBase.h"

namespace Electronics::Types {
    struct TiltCompensatedCompassSettings {
        // VERY IMPORTANT!
        // These are the previously determined offsets and scale factors for accelerometer and magnetometer, using ICM_20948_cal and Magneto
        // The compass will NOT work well or at all if these are not correct
        // https://github.com/jremington/ICM_20948-AHRS

        // Accel scale: divide by 16604.0 to normalize. These corrections are quite small and probably can be ignored.
        float A_B[3] = {  79.60,  -18.56,  383.31 };
        float A_Ainv[3][3] ={
            {  1.00847,  0.00470, -0.00428 },
            {  0.00470,  1.00846, -0.00328 },
            { -0.00428, -0.00328,  0.99559 }
        };

        // Mag scale divide by 369.4 to normalize. These are significant corrections, especially the large offsets.
        float M_B[3] = { -156.70,  -52.79, -141.07 };
        float M_Ainv[3][3] = {
            {  1.12823, -0.01142,  0.00980 },
            { -0.01142,  1.09539,  0.00927 },
            {  0.00980,  0.00927,  1.10625 }
        };

        /// local magnetic declination in degrees
        float declination = 14.84;
        
        /// This tilt-compensated code assumes that the ICM_90248 sensor board is oriented
        /// with Accel X pointing to the North, Y pointing West, and Z pointing up for heading = 0 degrees.
        /// The code compensates for tilts of up to 90 degrees away from horizontal.
        /// Facing vector p is the direction of travel and allows reassigning these directions.
        /// It should be defined as pointing forward,
        /// parallel to the ground, with coordinates {X, Y, Z} (in magnetometer frame of reference).
        /// For example, if the sensor board is mounted flat on a vehicle, facing forward, p = {1, 0, 0}.
        /// if the sensor board is mounted flat on a vehicle, facing to the right, p = {0, 1, 0}.
        /// Idk if this is clear, just make electrical not point the magnetometer in a weird direction.
        float facingVector[3] = {1.0f, 0.0f, 0.0f};
    };

    class TiltCompensatedCompassBase : public MagnetometerBase {
    public:
        explicit TiltCompensatedCompassBase(TiltCompensatedCompassSettings &settings);

        /// Returns the current heading of the magnetometer. Measured in degrees from 0 to 360. 0 is north, 90 is east, 180 is south, 270 is west.
        double GetHeading() override;

    protected:
        TiltCompensatedCompassSettings m_Settings;
        double m_Heading = 0;

        /// Calculates the heading based on the accelerometer and magnetometer data.
        double calculateHeading(float accelerometerVector[3], float magnetometerVector[3]);

        /// Subtracts offsets and correction matrix to accel and mag data
        void scale_IMU(float accelerometerVector[3], float magnetometerVector[3]);

        // basic vector operations
        static void vector_cross(float a[3], float b[3], float out[3]);
        static float vector_dot(float a[3], float b[3]);
        static void vector_normalize(float a[3]);
    };
}
