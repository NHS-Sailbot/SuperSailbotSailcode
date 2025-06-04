/// Created by Computery on 11/6/2024.

#pragma once

#include "ICM_20948.h"
#include "Electronics/Types/Magnetometer/TiltCompensatedCompassBase.h"

namespace Electronics::Implementations::Magnetometers {
    class SparkFunICM20948 final : public Types::TiltCompensatedCompassBase {
    public:
        SparkFunICM20948(Types::TiltCompensatedCompassSettings settings, MbedI2C& i2cWire, uint8_t address);

        void Update() override;

        Types::MagnetometerCalibrationStatus GetCalibration() override;

    private:
        ICM_20948_I2C m_SparkFunICM20948;

        float acc[3] = {0, 0, 0};
        float mag[3] = {0, 0, 0};
        Types::MagnetometerCalibrationStatus m_Calibration = Types::MagnetometerCalibrationStatus::NotCalibrated;
    };
}
