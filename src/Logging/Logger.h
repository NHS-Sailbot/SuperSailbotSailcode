/// Created by Computery on 9/19/2024.

#pragma once

#include <Arduino.h>

namespace Logging {
    class Logger {
    public:
         static void Start(HardwareSerial *serial, const unsigned long baudRate) {
            LoggingSerial = serial;
            LoggingSerial->begin(baudRate);
            HasBegun = true;
        }
        /// Log a message to all active log outputs
        static void Log(const char *message, const bool newLine = true) {
            if (!HasBegun) { return; }
            LoggingSerial->print(message);
            if (newLine) { LoggingSerial->println(); }
        }
        /// Log a message to all active log outputs
        static void Log(const __FlashStringHelper *message, const bool newLine = true) {
            Log(reinterpret_cast<const char *>(message), newLine);
        }
    private:
        /// Is used to check if the logger has been started
        inline static bool HasBegun = false;
        /// The serial port to log to
        inline static HardwareSerial *LoggingSerial = nullptr;
    };
}