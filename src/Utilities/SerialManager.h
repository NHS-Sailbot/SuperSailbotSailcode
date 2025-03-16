/// Created by Computery on 3/15/2025.

#pragma once

#include <Arduino.h>
#include <map>
#include <sys/_intsup.h>

#include "LEDStuff.h"

namespace Utilitys {
    struct SerialSettings {
        HardwareSerial *serial = &Serial;
        unsigned long baudRate = 115200;
    };
    
    class SerialManager {
    public:
        inline static bool HasStarted = false;
        inline static SerialSettings Settings;
    
        static void Start(const SerialSettings settings = SerialSettings()) {
            if (HasStarted) { return; }
            Settings = settings;
            Settings.serial->setTimeout(5000); // Set a timeout for serial reads
            Settings.serial->begin(settings.baudRate);
            HasStarted = true;

            RegisterCallback(IdentifyDevice, 255); // Register a callback for the unique identifier

            LEDStuff::SetRGB(false, true, false);
            delay(10000); // Allow time for the serial connection to establish, this takes sooo long
            LEDStuff::SetRGB(false, false, false);
        }

        static void IdentifyDevice() {
            Settings.serial->write(reinterpret_cast<const char*>(80085), 4); // Send a unique identifier to the serial port

            LEDStuff::SetRGB(true, true, true);
            delay(10000);
            LEDStuff::SetRGB(false, false, false);
        }
        
        static HardwareSerial &GetSerial() {
            if (!HasStarted) { Start();} // Ensure Serial is started before returning
            return *Settings.serial;
        }

        static void Update() {
            if (!HasStarted) { Start(); } // Ensure Serial is started before updating
            if (Settings.serial->available()) {
                int peekedType = Settings.serial->peek();

                GetSerial().print(F("Peeked Type: "));
                GetSerial().println(peekedType);
                int a = 80085;
                GetSerial().print(static_cast<char*>(static_cast<void*>(&a)));
                
                if (callbacks.count(peekedType) > 0) {
                    callbacks[peekedType](); // Call the registered callback for the peeked type
                } else {
                    Settings.serial->read(); // Read and discard if no callback is registered
                    LEDStuff::SetRGB(true, false, false);
                    delay(1000); // Indicate no callback was found
                    LEDStuff::SetRGB(false, false, false);
                }
            } else {
                LEDStuff::SetRGB(false, false, false);
            }
        }

        static bool RegisterCallback(const std::function<void()>& callback, const uint8_t index) {
            if (callbacks.find(index) != callbacks.end()) {
                return false; // Callback already exists at this index
            }
            callbacks[index] = callback;
            return true; // Callback registered successfully
        }

        static bool DeregisterCallback(int index) {
            auto it = callbacks.find(index);
            if (it != callbacks.end()) {
                callbacks.erase(it);
                return true; // Callback deregistered successfully
            }
            return false; // No callback found at this index
        }

        inline static std::map<int, std::function<void()>> callbacks = {};
    };
}
