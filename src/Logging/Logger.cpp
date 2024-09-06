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

    void Logger::Print(const char* message) {
        LoggerSerial->print(message);
    }
    void Logger::PrintLine(const char* message) {
        Print(message);
        Print("\n");
    }

    void Logger::Print(const __FlashStringHelper* message) {
        PrintFlashStringHelper(message);
    }
    void Logger::PrintLine(const __FlashStringHelper* message) {
        PrintFlashStringHelper(message);
        Print("\n");
    }
    const char* Logger::PrintFlashStringHelper(const __FlashStringHelper *message) {
#if defined(__AVR__) // This is some AVR-specific code, idk what it's doing or how it works. Taken from Print.cpp.
        PGM_P p = reinterpret_cast<PGM_P>(message);
        while (true) {
            char c = pgm_read_byte(p++);
            if (c == 0) { break; }
            Print(&c);
        }
#else
        Print(reinterpret_cast<const char *>(message));
#endif
    }
}
