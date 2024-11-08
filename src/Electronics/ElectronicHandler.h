/// Created by Computery on 9/19/2024.

#pragma once

#include "Types/Gps/GpsBase.h"
#include "Logging/Logger.h"
#include <Wire.h>
#include "Implementations/GPS/UBlox/UbloxGpsI2c.h"
#include "Implementations/LimitSwitches/InterruptLimitSwitchMethod.h"
#include "Implementations/Magnetometers/SparkFunICM20948.h"
#include "Implementations/Servos/ArduinoServo.h"
#include "Implementations/WindSensors/AnalogWindSensorWithMagnetometerCorrection.h"
#include "Types/Magnetometer/MagnetometerBase.h"
#include "Types/Servo/ServoBase.h"
#include "Types/WindSensor/WindSensorBase.h"

using namespace Logging;

namespace Electronics {
    class ElectronicHandler {
    public:
        inline static Types::ServoBase *WinchServo = nullptr;
        inline static Types::LimitSwitchBase *MinLimitSwitchWinch = nullptr;
        inline static Types::LimitSwitchBase *MaxLimitSwitchWinch = nullptr;

        inline static Types::ServoBase *JibWinchServo = nullptr;
        inline static Types::ServoBase *RudderServo = nullptr;

        inline static Types::GpsBase *Gps = nullptr;
        inline static Types::WindSensorBase *WindSensor = nullptr;
        inline static Types::MagnetometerBase *Magnetometer = nullptr;

        static void Start() {
            Logger::Log(F("Starting electronics..."));

            Wire.begin();
            Wire.setClock(400000);

            WinchServo = new Implementations::Servos::ArduinoServo(9, 1080);
            MinLimitSwitchWinch = new Implementations::InterruptLimitSwitchMethod(2, [] {});
            MaxLimitSwitchWinch = new Implementations::InterruptLimitSwitchMethod(3, [] {});
            JibWinchServo = new Implementations::Servos::ArduinoServo(11, 180);
            RudderServo = new Implementations::Servos::ArduinoServo(10, 180);

            Gps = new Implementations::Gps::UbloxGpsI2c(&Wire, 66);
            Magnetometer = new Implementations::Magnetometers::SparkFunICM20948(&Wire, 68, {});
            WindSensor = new Implementations::WindSensors::AnalogWindSensorWithMagnetometerCorrection(A0, Magnetometer);
        }

        static void Update() {
            Gps->Update();
            WindSensor->Update();
            Magnetometer->Update();
        }
    };
}
