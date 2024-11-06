/// Created by Computery on 11/6/2024.

#include "SparkFunICM20948.h"
#include "Logging/Logger.h"

using namespace Electronics::Implementations;
using namespace Electronics::Types;

Magnetometers::SparkFunICM20948::SparkFunICM20948(MbedI2C *i2cWire, uint8_t address, TiltCompensatedCompassSettings settings) : TiltCompensatedCompassBase(settings) {
    if (m_SparkFunICM20948.begin(*i2cWire, address) != ICM_20948_Stat_Ok) {
        Logging::Logger::Log(F("ICM_20948 not detected at I2C address. Please check wiring."));
        m_Calibration = {
            NotCalibrated,
            NotCalibrated,
            NotCalibrated,
            NotCalibrated
        };
    } else {
        m_Calibration = {
            Calibrated,
            Calibrated,
            Calibrated,
            Calibrated
        };
    }
}

MagnetometerCalibration Magnetometers::SparkFunICM20948::Update() {
    if (m_SparkFunICM20948.dataReady()) { m_SparkFunICM20948.getAGMT(); }

    if (m_SparkFunICM20948.status != ICM_20948_Stat_Ok) {
        Logging::Logger::Log(F("Error reading magnetometer"));
        m_Calibration = {
            NotCalibrated,
            NotCalibrated,
            NotCalibrated,
            NotCalibrated
        };
        return m_Calibration;
    }

    m_Calibration = {
        Calibrated,
        Calibrated,
        Calibrated,
        Calibrated
    };

    acc[0] = m_SparkFunICM20948.agmt.acc.axes.x;
    acc[1] = m_SparkFunICM20948.agmt.acc.axes.y;
    acc[2] = m_SparkFunICM20948.agmt.acc.axes.z;
    mag[0] = m_SparkFunICM20948.agmt.mag.axes.x;
    mag[1] = m_SparkFunICM20948.agmt.mag.axes.y;
    mag[2] = m_SparkFunICM20948.agmt.mag.axes.z;

    m_Heading = calculateHeading(acc, mag);

    return m_Calibration;
}

MagnetometerCalibration Magnetometers::SparkFunICM20948::
GetCalibration() {
    return m_Calibration;
}
