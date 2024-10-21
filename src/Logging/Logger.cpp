/// Created by Computery on 9/19/2024.

#include "Logger.h"

namespace Logging {
    bool Logger::HasBegun = false;
    HardwareSerial *Logger::LoggingSerial = nullptr;

    void Logger::Begin(HardwareSerial *serial, const unsigned long baudRate) {
        LoggingSerial = serial;
        LoggingSerial->begin(baudRate);
        HasBegun = true;
    }

    void Logger::Log(const char *message, bool newLine) {
        if (!HasBegun) { return; }
        LoggingSerial->print(message);
        if (newLine) { LoggingSerial->println(); }
    }

    void Logger::Log(const __FlashStringHelper *message, bool newLine) {
        Log(reinterpret_cast<const char *>(message), newLine);
    }
}
