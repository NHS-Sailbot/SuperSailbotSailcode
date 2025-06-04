/// Created by Computery on 11/6/2024.

#include "SparkFunICM20948.h"
#include "Logging/Logger.h"

using namespace Electronics::Implementations;
using namespace Electronics::Types;
using namespace Logging;

Magnetometers::SparkFunICM20948::SparkFunICM20948(TiltCompensatedCompassSettings settings, MbedI2C& i2cWire = Wire, uint8_t address = 0x68) : TiltCompensatedCompassBase(settings) {
    Logger::Log(F("Initializing SparkFun ICM-20948 magnetometer..."));

    if (m_SparkFunICM20948.begin(i2cWire, address) != ICM_20948_Stat_Ok) {
        Logger::Log(F("ICM_20948 not detected at I2C address. Please check wiring."));
        m_Calibration = NotCalibrated;
        return;
    }

    m_Calibration = Calibrated;

    Logger::Log(F("SparkFun ICM-20948 magnetometer initialized!"));
}

void Magnetometers::SparkFunICM20948::Update() {
    if (m_SparkFunICM20948.dataReady()) { m_SparkFunICM20948.getAGMT(); }

    if (m_SparkFunICM20948.status != ICM_20948_Stat_Ok) {
        Logger::Log(F("Error reading magnetometer"));
        m_Calibration = NotCalibrated;
        return;
    }

    m_Calibration = Calibrated;

    acc[0] = m_SparkFunICM20948.agmt.acc.axes.x;
    acc[1] = m_SparkFunICM20948.agmt.acc.axes.y;
    acc[2] = m_SparkFunICM20948.agmt.acc.axes.z;
    mag[0] = m_SparkFunICM20948.agmt.mag.axes.x;
    mag[1] = m_SparkFunICM20948.agmt.mag.axes.y;
    mag[2] = m_SparkFunICM20948.agmt.mag.axes.z;

    m_Heading = calculateHeading(acc, mag);
}

MagnetometerCalibrationStatus Magnetometers::SparkFunICM20948::GetCalibration() {
    return m_Calibration;
}
