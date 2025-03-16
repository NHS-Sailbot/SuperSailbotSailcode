/// Created by Computery on 11/8/2024.

#include "TiltCompensatedCompassBase.h"
#include <Arduino.h>

namespace Electronics::Types {
    TiltCompensatedCompassBase::TiltCompensatedCompassBase(TiltCompensatedCompassSettings &settings): m_Settings(settings) {}

    double TiltCompensatedCompassBase::GetHeading() {
        return m_Heading;
    }

    double TiltCompensatedCompassBase::calculateHeading(float accelerometerVector[3], float magnetometerVector[3]) {
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

        double h = -atan2(vector_dot(W, m_Settings.facingVector), vector_dot(N, m_Settings.facingVector)) * 180 / M_PI;
        //minus: conventional nav, heading increases North to East
        double heading = h + m_Settings.declination;
        heading = fmod(heading + 360, 360); //apply compass wrap
        return heading;
    }

    void TiltCompensatedCompassBase::scale_IMU(float accelerometerVector[3], float magnetometerVector[3]) {
        float temp[3];
        // apply offsets (bias) and scale factors from Magneto
        for (uint8_t i = 0; i < 3; i++) { temp[i] = (accelerometerVector[i] - m_Settings.A_B[i]); }
        accelerometerVector[0] = m_Settings.A_Ainv[0][0] * temp[0] + m_Settings.A_Ainv[0][1] * temp[1] + m_Settings.A_Ainv[0][2] * temp[2];
        accelerometerVector[1] = m_Settings.A_Ainv[1][0] * temp[0] + m_Settings.A_Ainv[1][1] * temp[1] + m_Settings.A_Ainv[1][2] * temp[2];
        accelerometerVector[2] = m_Settings.A_Ainv[2][0] * temp[0] + m_Settings.A_Ainv[2][1] * temp[1] + m_Settings.A_Ainv[2][2] * temp[2];
        vector_normalize(accelerometerVector);

        // apply offsets (bias) and scale factors from Magneto
        for (uint8_t i = 0; i < 3; i++) { temp[i] = (magnetometerVector[i] - m_Settings.M_B[i]); }
        magnetometerVector[0] = m_Settings.M_Ainv[0][0] * temp[0] + m_Settings.M_Ainv[0][1] * temp[1] + m_Settings.M_Ainv[0][2] * temp[2];
        magnetometerVector[1] = m_Settings.M_Ainv[1][0] * temp[0] + m_Settings.M_Ainv[1][1] * temp[1] + m_Settings.M_Ainv[1][2] * temp[2];
        magnetometerVector[2] = m_Settings.M_Ainv[2][0] * temp[0] + m_Settings.M_Ainv[2][1] * temp[1] + m_Settings.M_Ainv[2][2] * temp[2];

        vector_normalize(magnetometerVector);
    }

    // basic vector operations
    void TiltCompensatedCompassBase::vector_cross(float a[3], float b[3], float out[3]) {
        out[0] = a[1] * b[2] - a[2] * b[1];
        out[1] = a[2] * b[0] - a[0] * b[2];
        out[2] = a[0] * b[1] - a[1] * b[0];
    }

    float TiltCompensatedCompassBase::vector_dot(float a[3], float b[3]) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    void TiltCompensatedCompassBase::vector_normalize(float a[3]) {
        float mag = sqrt(vector_dot(a, a));
        a[0] /= mag;
        a[1] /= mag;
        a[2] /= mag;
    }
}
