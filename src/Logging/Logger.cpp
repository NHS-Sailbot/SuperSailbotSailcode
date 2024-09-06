// Preprocessor directives: ARDUINO_AVR_MEGA2560, ARDUINO_GIGA_M7

#include "Logger.h"

namespace Logging {
    bool Logger::IsSetup = false;
    HardwareSerial *Logger::LoggerSerial = nullptr;

    void Logger::SetupLogging(HardwareSerial *serial) {
        LoggerSerial = serial;
        LoggerSerial->begin(LOGGER_BAUD_RATE);
        IsSetup = true;
    }

    void Logger::PrintLine(const char *message) {
        Print(message);
        Print("\n");
    }

    void Logger::Print(const char *message) {
        LoggerSerial->print(message);
    }

    void Logger::PrintLine(const __FlashStringHelper *message) {
        PrintLine(FlashStringHelperToString(message));
    }
    void Logger::Print(const __FlashStringHelper *message) {
        Print(FlashStringHelperToString(message));
    }

    const char * Logger::FlashStringHelperToString(const __FlashStringHelper *message) {
        return reinterpret_cast<const char *>(message);
    }
}
