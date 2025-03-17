/// Created by Computery on 9/19/2024.

#pragma once

#include "Types/Gps/GpsBase.h"
#include "Types/LimitSwitch/LimitSwitchBase.h"
#include "Types/Magnetometer/MagnetometerBase.h"
#include "Types/Servo/ServoBase.h"
#include "Types/WindSensor/WindSensorBase.h"

namespace Electronics {
    class ElectronicsManager {
    public:
        inline static Types::ServoBase *WinchServo = nullptr;
        inline static Types::LimitSwitchBase *MinLimitSwitchWinch = nullptr;
        inline static Types::LimitSwitchBase *MaxLimitSwitchWinch = nullptr;
        inline static Types::ServoBase *JibWinchServo = nullptr;
        inline static Types::ServoBase *RudderServo = nullptr;
        inline static Types::GpsBase *Gps = nullptr;
        inline static Types::WindSensorBase *WindSensor = nullptr;
        inline static Types::MagnetometerBase *Magnetometer = nullptr;

        /// Initializes all electronics
        static void Start();

        /// Updates all electronics
        static void Update();

        static void SendTelemetry();
    };
}
