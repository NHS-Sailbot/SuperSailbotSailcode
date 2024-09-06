#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <HardwareSerial.h>

namespace Logging {

class Logger {
public:
    static void SetupLogging(HardwareSerial* serial);
    static void PrintLine(const char* message);
    static void Print(const char* message);

    static void PrintLine(const __FlashStringHelper * message);
    static void Print(const __FlashStringHelper * message);

private:
    static const char* PrintFlashStringHelper(const __FlashStringHelper* message);
    static bool IsSetup;
    static HardwareSerial* LoggerSerial;
    static constexpr unsigned long LOGGER_BAUD_RATE = 9600;
};

}

#endif
