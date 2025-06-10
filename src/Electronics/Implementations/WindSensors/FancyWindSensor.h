#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "Electronics/Types/WindSensor/WindSensorBase.h"
#include "Electronics/Types/Magnetometer/MagnetometerBase.h"

namespace Electronics::Implementations::WindSensors {
	class FancyWindSensor final : public Types::WindSensorBase {
	public:
		FancyWindSensor(double offset, HardwareSerial& serialPort = Serial1) {
			m_Offset = offset;
			m_SerialPort = &serialPort;
		}

		void Update() override {
		}

		double GetDirection() override {
			return m_WindDirection;
		}

	private:
		const uint8_t register_to_read = 0x10;
		double m_Offset = 0;
		double m_WindDirection = 0;
		HardwareSerial* m_SerialPort;
		Types::MagnetometerBase* m_Magnetometer;
	};
}