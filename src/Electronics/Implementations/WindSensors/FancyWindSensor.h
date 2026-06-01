#pragma once

#include <Arduino.h>
#include "Electronics/Types/WindSensor/WindSensorBase.h"
#include "Utilities/Degrees.h"

namespace Electronics::Implementations::WindSensors {
    class FancyWindSensor final : public Types::WindSensorBase {
    public:
        static constexpr size_t kMaxLineLength = 1024; // TODO: Check an example output and decrease this number. This is like absolutely way too big.

        FancyWindSensor(double offset, HardwareSerial& serialPort = Serial3, long baudRate = 115200) : m_Offset(offset), m_SerialPort(&serialPort) {
            m_SerialPort->begin(baudRate);
        }

        void Update() override {
            while (m_SerialPort->available() > 0) {
                const char c = static_cast<char>(m_SerialPort->read());

                if (c == '\r') { continue; }

                if (c == '\n') {
                    m_LineBuffer[m_LineLength] = '\0';
                    int direction = 0;
                    if (TryParseWindDirection(m_LineBuffer, direction)) {
                        m_WindDirection = Degrees::Wrap360(static_cast<double>(direction) + m_Offset);
                    }
                    ResetLineBuffer();
                    continue;
                }

                if (m_LineLength + 1 >= kMaxLineLength) {
                    ResetLineBuffer();
                    continue;
                }

                m_LineBuffer[m_LineLength++] = c;
            }
        }

        double GetDirection() override {
            return m_WindDirection;
        }

    private:
        static bool TryParseWindDirection(const char* line, int& outDirection) {
            const char* firstComma = strchr(line, ',');
            if (firstComma == nullptr) { return false; }

            const char* secondComma = strchr(firstComma + 1, ',');
            if (secondComma == nullptr) { return false; }

            const size_t fieldLen = static_cast<size_t>(secondComma - (firstComma + 1));
            if (fieldLen == 0 || fieldLen >= 16) { return false; }

            char field[16];
            memcpy(field, firstComma + 1, fieldLen);
            field[fieldLen] = '\0';

            char* end = nullptr;
            const long value = strtol(field, &end, 10);
            if (end == field) { return false; }

            outDirection = static_cast<int>(value);
            return true;
        }

        void ResetLineBuffer() {
            m_LineLength = 0;
            m_LineBuffer[0] = '\0';
        }

        char m_LineBuffer[kMaxLineLength] = {};
        size_t m_LineLength = 0;
        double m_Offset = 0.0;
        double m_WindDirection = 0.0;
        HardwareSerial* m_SerialPort = nullptr;
    };
}
