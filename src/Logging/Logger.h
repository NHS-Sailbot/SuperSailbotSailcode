/// Created by Computery on 9/19/2024.

#pragma once

#include <Arduino.h>

namespace Logging {
    struct LoggerSettings {
        HardwareSerial *serial = &Serial;
        unsigned long baudRate = 115200;
    };

    class Logger {
    public:
        static void Start(LoggerSettings settings = {}) {
            LoggingSettings = settings;
            LoggingSettings.serial->begin(settings.baudRate);
            HasBegun = true;

            delay(2500); // This is here so we can see the start of the program in the serial monitor

            Log(F("Logger started!"));

            Log(F("Pre-start logs:"));
            for (const char *log : PreStartLogs) {
                Log(log);
            }
            PreStartLogs.clear();
        }

        /// Log a message to all active log outputs
        static void Log(const char *message, const bool newLine = true) {
            if (!HasBegun) {
                PreStartLogs.push_back(message);
                return;
            }
            LoggingSettings.serial->print(message);
            if (newLine) { LoggingSettings.serial->println(); }
        }

        /// Log a message to all active log outputs
        static void Log(const __FlashStringHelper *message, const bool newLine = true) {
            Log(reinterpret_cast<const char *>(message), newLine);
        }
    private:
        /// Is used to check if the logger has been started
        inline static bool HasBegun = false;

        /// The serial port to log to
        inline static LoggerSettings LoggingSettings = {};

        /// Vector of things logged before the logger was started
        inline static std::vector<const char *> PreStartLogs;
    };
}