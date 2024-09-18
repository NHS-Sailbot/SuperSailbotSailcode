#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <vector>

namespace Logging {

class Logger {
public:
    static void Begin(HardwareSerial* serial, unsigned long baudRate);
    static void Print(const char* message);
    static void Println(const char* message);
    static void Print(const __FlashStringHelper* message);
    static void Println(const __FlashStringHelper* message);
private:
    static bool HasBegun;
    static HardwareSerial* LoggingSerial;
    static void PrintToSerial(const char* message);
    static void PrintToFile(const char* message);
};

}


#endif