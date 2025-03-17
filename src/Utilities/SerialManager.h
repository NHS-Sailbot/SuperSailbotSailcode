/// Created by Computery on 3/15/2025.

#pragma once

#include <Arduino.h>
#include <map>

namespace Utilitys {
    struct SerialSettings {
        HardwareSerial *serial = &Serial;
        unsigned long baudRate = 115200;
    };
    
    class SerialManager {
    public:
        inline static bool HasStarted = false;
        inline static bool FoundApi = false;
        
        inline static SerialSettings Settings;
    
        static void Start(SerialSettings settings = SerialSettings());

        static void IdentifyDevice();

        static HardwareSerial &GetSerial();

        static void Update();

        static bool RegisterCallback(const std::function<void()>& callback, const uint8_t index);

        static bool DeregisterCallback(int index);

        inline static std::map<int, std::function<void()>> callbacks = {};
    };
}
