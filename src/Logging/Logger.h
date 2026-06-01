/// Created by Computery on 9/19/2024.

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Utilities/SerialManager.h"

using namespace Utilitys;

namespace Logging {
    // TODO: You're going to want to implement the Arduino Gigas USB support here and make sure that it saves to a file on that USB.
    class Logger {
    public:
        static void Start() {
            if (HasBegun) { return; } // Prevent starting the logger multiple times
            HasBegun = true;
            
            Log(F("Logger started!"));

            Log(F("Pre-start logs:"));
            for (const __FlashStringHelper* log : PreStartFlashLogs) { Log(log); }
            PreStartFlashLogs.clear();
            for (const char* log : PreStartRamLogs) { Log(log); }
            PreStartRamLogs.clear();
            for (const String& log : PreStartJsonLogs) { Log(log); }
            PreStartJsonLogs.clear();
        }

        static void Log(const char* message, const bool newLine = true) {
            if (!HasBegun) {
                PreStartRamLogs.push_back(message);
                return;
            }
            writeToSerial(message, newLine);
        }

        static void Log(const String& message, const bool newLine = true) {
            if (!HasBegun) {
                PreStartRamLogs.push_back(message.c_str());
                return;
            }
            writeToSerial(message, newLine);
        }

        static void Log(const __FlashStringHelper* message, const bool newLine = true) {
            if (!HasBegun) {
                PreStartFlashLogs.push_back(message);
                return;
            }
            writeToSerial(message, newLine);
        }

        static void LogJson(JsonVariantConst json, const bool newLine = true) {
            if (!HasBegun) {
                String serialized;
                serializeJson(json, serialized);
                PreStartJsonLogs.push_back(std::move(serialized));
                return;
            }
            serializeJson(json, SerialManager::GetSerial());
            if (newLine) { SerialManager::GetSerial().println(); }
        }

    private:
        static void writeToSerial(const char* message, const bool newLine) {
            SerialManager::GetSerial().print(message);
            if (newLine) { SerialManager::GetSerial().println(); }
        }

        static void writeToSerial(const __FlashStringHelper* message, const bool newLine) {
            SerialManager::GetSerial().print(message);
            if (newLine) { SerialManager::GetSerial().println(); }
        }

        static void writeToSerial(const String& message, const bool newLine) {
            SerialManager::GetSerial().print(message);
            if (newLine) { SerialManager::GetSerial().println(); }
        }

        inline static bool HasBegun = false;

        inline static std::vector<const __FlashStringHelper*> PreStartFlashLogs;
        inline static std::vector<const char*> PreStartRamLogs;
        inline static std::vector<String> PreStartJsonLogs;
    };
}
