#include "Logger.h"

namespace Logging {
    bool Logger::HasBegun = false;
    HardwareSerial *Logger::LoggingSerial = nullptr;

    void Logger::Begin(HardwareSerial *serial, const unsigned long baudRate) {
        LoggingSerial = serial;
        LoggingSerial->begin(baudRate);
        HasBegun = true;
    }

    void Logger::Print(const char *message) {
        PrintToSerial(message);
        PrintToFile(message);
    }

    void Logger::Println(const char *message) {
        PrintToSerial(message);
        PrintToSerial("\n");
        PrintToFile(message);
        PrintToSerial("\n");
    }

    void Logger::Print(const __FlashStringHelper *message) {
#if defined(__AVR__)
        PGM_P p = reinterpret_cast<PGM_P>(message);
        while (true) {
            char c = pgm_read_byte(p++);
            if (c == 0) { break; }
            PrintToSerial(&c);
            PrintToFile(&c);
        }
#else
        const char *messagePtr = reinterpret_cast<const char *>(message);
        PrintToSerial(messagePtr);
        PrintToFile(messagePtr);
#endif
    }

    void Logger::Println(const __FlashStringHelper *message) {
        Print(message);
        Print("\n");
    }

    void Logger::PrintToSerial(const char *message) {
        LoggingSerial->print(message);
    }

    void Logger::PrintToFile(const char *message) {
    }
}
