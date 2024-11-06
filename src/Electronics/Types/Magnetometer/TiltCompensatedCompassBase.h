/// Created by Computery on 11/6/2024.

#pragma once

#include "MagnetometerBase.h"

namespace Electronics::Types {
    struct TiltCompensatedCompassSettings {
        // VERY IMPORTANT!
        //These are the previously determined offsets and scale factors for accelerometer and magnetometer, using ICM_20948_cal and Magneto
        //The compass will NOT work well or at all if these are not correct

        //Accel scale: divide by 16604.0 to normalize. These corrections are quite small and probably can be ignored.
        float A_B[3] = {  79.60,  -18.56,  383.31};
        float A_Ainv[3][3] ={
            {  1.00847,  0.00470, -0.00428},
            {  0.00470,  1.00846, -0.00328},
            { -0.00428, -0.00328,  0.99559}
        };

        //Mag scale divide by 369.4 to normalize. These are significant corrections, especially the large offsets.
        float M_B[3] = { -156.70,  -52.79, -141.07};
        float M_Ainv[3][3] ={
            {  1.12823, -0.01142,  0.00980},
            { -0.01142,  1.09539,  0.00927},
            {  0.00980,  0.00927,  1.10625}
        };

        // local magnetic declination in degrees
        float declination = 14.84;

        /*
        This tilt-compensated code assumes that the ICM_90248 sensor board is oriented with Accel X pointing
        to the North, Y pointing West, and Z pointing up for heading = 0 degrees
        The code compensates for tilts of up to 90 degrees away from horizontal.
        Facing vector p is the direction of travel and allows reassigning these directions.
        It should be defined as pointing forward,
        parallel to the ground, with coordinates {X, Y, Z} (in magnetometer frame of reference).
        */
        float p[3] = {1.0f, 0.0f, 0.0f};  //X marking on sensor board points toward yaw = 0
    };

    class TiltCompensatedCompassBase : public MagnetometerBase {
    public:
        explicit TiltCompensatedCompassBase(const TiltCompensatedCompassSettings &settings) : m_Settings(settings) {}

        double GetHeading() override {
            return m_Heading;
        }
    protected:
        TiltCompensatedCompassSettings m_Settings;
        double m_Heading = 0;

        double calculateHeading(float accelerometerVector[3], float magnetometerVector[3]) {
            scale_IMU(accelerometerVector, magnetometerVector);

            //align magnetometer with accelerometer (reflect Y and Z)
            magnetometerVector[1] = -magnetometerVector[1];
            magnetometerVector[2] = -magnetometerVector[2];

            float W[3], N[3]; //derived direction vectors

            // cross "Up" (acceleration vector, g) with magnetic vector (magnetic north + inclination) with  to produce "West"
            vector_cross(accelerometerVector, magnetometerVector, W);
            vector_normalize(W);

            // cross "West" with "Up" to produce "North" (parallel to the ground)
            vector_cross(W, accelerometerVector, N);
            vector_normalize(N);

            // compute heading in horizontal plane, correct for local magnetic declination in degrees

            double h = -atan2(vector_dot(W, m_Settings.p), vector_dot(N, m_Settings.p)) * 180 / M_PI; //minus: conventional nav, heading increases North to East
            double heading = round(h + m_Settings.declination);
            heading = fmod(heading + 360, 360); //apply compass wrap
            return heading;
        }

        // subtract offsets and correction matrix to accel and mag data
        void scale_IMU(float accelerometerVector[3], float magnetometerVector[3]) {
            float temp[3];
            //apply offsets (bias) and scale factors from Magneto
            for (uint8_t i = 0; i < 3; i++) { temp[i] = (accelerometerVector[i] - m_Settings.A_B[i]); }

            accelerometerVector[0] = m_Settings.A_Ainv[0][0] * temp[0] + m_Settings.A_Ainv[0][1] * temp[1] + m_Settings.A_Ainv[0][2] * temp[2];
            accelerometerVector[1] = m_Settings.A_Ainv[1][0] * temp[0] + m_Settings.A_Ainv[1][1] * temp[1] + m_Settings.A_Ainv[1][2] * temp[2];
            accelerometerVector[2] = m_Settings.A_Ainv[2][0] * temp[0] + m_Settings.A_Ainv[2][1] * temp[1] + m_Settings.A_Ainv[2][2] * temp[2];
            vector_normalize(accelerometerVector);

            //apply offsets (bias) and scale factors from Magneto
            for (uint8_t i = 0; i < 3; i++) { temp[i] = (magnetometerVector[i] - m_Settings.M_B[i]); }
            magnetometerVector[0] = m_Settings.M_Ainv[0][0] * temp[0] + m_Settings.M_Ainv[0][1] * temp[1] + m_Settings.M_Ainv[0][2] * temp[2];
            magnetometerVector[1] = m_Settings.M_Ainv[1][0] * temp[0] + m_Settings.M_Ainv[1][1] * temp[1] + m_Settings.M_Ainv[1][2] * temp[2];
            magnetometerVector[2] = m_Settings.M_Ainv[2][0] * temp[0] + m_Settings.M_Ainv[2][1] * temp[1] + m_Settings.M_Ainv[2][2] * temp[2];

            vector_normalize(magnetometerVector);
        }

        // basic vector operations
        static void vector_cross(float a[3], float b[3], float out[3]){
            out[0] = a[1] * b[2] - a[2] * b[1];
            out[1] = a[2] * b[0] - a[0] * b[2];
            out[2] = a[0] * b[1] - a[1] * b[0];
        }
        static float vector_dot(float a[3], float b[3]){
            return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
        }
        static void vector_normalize(float a[3]){
            float mag = sqrt(vector_dot(a, a));
            a[0] /= mag;
            a[1] /= mag;
            a[2] /= mag;
        }
    };
}
