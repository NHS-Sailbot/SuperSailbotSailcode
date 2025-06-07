#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "Electronics/Types/WindSensor/WindSensorBase.h"
#include "Electronics/Types/Magnetometer/MagnetometerBase.h"

namespace Electronics::Implementations::WindSensors {
	class FancyWindSensor final : public Types::WindSensorBase {
	public:
		FancyWindSensor(Types::MagnetometerBase* magnetometer, double offset, MbedI2C& wire, uint8_t address = 0x15) {
			m_Offset = offset;
			m_Magnetometer = magnetometer;
			m_Wire = &wire;
			m_Address = address;
			
			m_Wire->beginTransmission(m_Address);
			m_Wire->write(register_to_read);
			m_Wire->endTransmission(false);
		}

		void Update() override {
			m_Wire->requestFrom(m_Address, 2);
			if (m_Wire->available() >= 2) {
				uint8_t mostSignificantByte = m_Wire->read();
				uint8_t leastSignificantByte = m_Wire->read();

				// Combine the two bytes into a single 16-bit value.
				uint16_t raw_value = (mostSignificantByte << 8) | leastSignificantByte;
				
				double windDirectionFromSensor = static_cast<double>(raw_value) * 360.0 / 65535.0;

				m_WindDirection = fmod(windDirectionFromSensor + m_Offset + m_Magnetometer->GetHeading(), 360.0);
			} else {
				m_WindDirection = -1.0;
			}
		}

		double GetDirection() override {
			return m_WindDirection;
		}

	private:
		const uint8_t register_to_read = 0x10;
		double m_Offset = 0;
		double m_WindDirection = 0;
		uint8_t m_Address = 0x15;
		MbedI2C* m_Wire;
		Types::MagnetometerBase* m_Magnetometer;
	};
}