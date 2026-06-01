#pragma once

#include <Arduino.h>
#include "Electronics/Types/WindSensor/WindSensorBase.h"
#include "Utilities/Degrees.h"

namespace Electronics::Implementations::WindSensors {
	class FancyWindSensor final : public Types::WindSensorBase {
	public:
		FancyWindSensor(double offset, HardwareSerial& serialPort = Serial3, long buadRate = 115200) {
			m_Offset = offset;
			m_SerialPort = &serialPort;
			m_SerialPort->begin(buadRate);
		}

		void Update() override {
			int availableBytes = m_SerialPort->available();
			if (availableBytes) {
				for (int i = 0; i < availableBytes; i++) {
					char read = m_SerialPort->read();
					if (read == '\n') {
						int first = m_ReadString.indexOf(',');
						int second = m_ReadString.indexOf(',', first + 1);
						String subString = m_ReadString.substring(first + 1, second);
						m_WindDirection = Degrees::Wrap360(subString.toInt() + m_Offset);

						Logging::Logger::Log(F("Wind Direction: "), false);
						Logging::Logger::Log(String(m_WindDirection));

						m_ReadString = "";
					} else { m_ReadString += read; }
				}
			}
		}

		double GetDirection() override {
			return m_WindDirection;
		}

	private:
		String m_ReadString = "";
		double m_Offset = 0;
		double m_WindDirection = 0;
		HardwareSerial* m_SerialPort;
	};
}