/// Created by Computery on 9/19/2024.

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

namespace Logging {
    class Logger {
    public:
        /// Begin logging
        static void Begin(HardwareSerial *serial, unsigned long baudRate);

        /// Log a message
        static void Log(const char *message, bool newLine = true);

        /// Log a message
        static void Log(const __FlashStringHelper *message, bool newLine = true);

    private:
        /// Is used to check if the logger has been started
        static bool HasBegun;
        /// The serial port to log to
        static HardwareSerial *LoggingSerial;
    };
}

#endif
