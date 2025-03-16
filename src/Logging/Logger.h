/// Created by Computery on 9/19/2024.

#pragma once

#include <Arduino.h>

#include "Utilities/SerialManager.h"

using namespace Utilitys;

namespace Logging {
    class Logger {
    public:
        static void Start() {
            if (HasBegun) { return; } // Prevent starting the logger multiple times
            HasBegun = true;
            
            Log(F("Logger started!"));

            Log(F("Pre-start logs:"));
            for (const char *log : PreStartLogs) {Log(log);}
            PreStartLogs.clear();
        }

        /// Log a message to all active log outputs
        static void Log(const char *message, const bool newLine = true) {
            if (!HasBegun) {
                PreStartLogs.push_back(message);
                return;
            }

            // Serial Logging
            SerialManager::GetSerial().print(message);
            if (newLine) {SerialManager::GetSerial().println();}
        }

        static void Log(const String& message, const bool newLine = true) {
            if (!HasBegun) {
                PreStartLogs.push_back(message.c_str());
                return;
            }

            // Serial Logging
            SerialManager::GetSerial().print(message);
            if (newLine) {SerialManager::GetSerial().println();}
        }

        /// Log a message to all active log outputs
        static void Log(const __FlashStringHelper *message, const bool newLine = true) {
            Log(reinterpret_cast<const char *>(message), newLine);
        }
    private:
        /// Is used to check if the logger has been started
        inline static bool HasBegun = false;

        /// Vector of things logged before the logger was started
        inline static std::vector<const char *> PreStartLogs;
    };
}
