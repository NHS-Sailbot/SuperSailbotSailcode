/// Created by Computery on 9/19/2024.

#pragma once

#include "Implementations/GPS/UbloxGpsI2c.h"
#include "Types/Gps/GpsBase.h"
#include "Logging/Logger.h"
#include <Wire.h>

#include "Implementations/LimitSwitches/InterruptLimitSwitchMethod.h"
#include "Implementations/Magnetometer/SparkFunICM20948.h"
#include "Implementations/Servos/ArduinoServo.h"
#include "Implementations/WindSensors/AnalogWindSensorWithMagnetometerCorrection.h"
#include "Types/ServoBase.h"
#include "Types/WindSensorBase.h"
#include "Types/Magnetometer/MagnetometerBase.h"

using namespace Logging;
using namespace Electronics::Types;

namespace Electronics {
    class BoatElectronics {
    public:
        inline static ServoBase *WinchServo = nullptr;
        inline static InterruptLimitSwitchMethod *MinLimitSwitchWinch = nullptr;
        inline static InterruptLimitSwitchMethod *MaxLimitSwitchWinch = nullptr;

        inline static ServoBase *JibWinchServo = nullptr;
        inline static InterruptLimitSwitchMethod *MinLimitSwitchJibWinch = nullptr;
        inline static InterruptLimitSwitchMethod *MaxLimitSwitchJibWinch = nullptr;

        inline static ServoBase *RudderServo = nullptr;

        inline static GpsBase *Gps = nullptr;

        inline static MagnetometerBase *Magnetometer = nullptr;
        inline static TiltCompensatedCompassSettings tiltCompensatedCompassSettings = {
            {  79.60,  -18.56,  383.31},
            {
                {  1.00847,  0.00470, -0.00428},
                {  0.00470,  1.00846, -0.00328},
                { -0.00428, -0.00328,  0.99559}
            },
            { -156.70,  -52.79, -141.07},
            {
                {  1.12823, -0.01142,  0.00980},
                { -0.01142,  1.09539,  0.00927},
                {  0.00980,  0.00927,  1.10625}
            },
            14.84,
            {1.0f, 0.0f, 0.0f}
        };

        inline static WindSensorBase *WindSensor = nullptr;

        static void Start() {
            Logger::Log(F("Starting electronics..."));

            Wire.begin();
            Wire.setClock(400000);

            WinchServo = new Implementations::Servos::ArduinoServo(9, 180);
            MinLimitSwitchWinch = new InterruptLimitSwitchMethod(2, [] {
            });
            MaxLimitSwitchWinch = new InterruptLimitSwitchMethod(3, [] {
            });

            JibWinchServo = new Implementations::Servos::ArduinoServo(11, 180);
            MinLimitSwitchJibWinch = new InterruptLimitSwitchMethod(4, [] {
            });
            MaxLimitSwitchJibWinch = new InterruptLimitSwitchMethod(5, [] {
            });

            RudderServo = new Implementations::Servos::ArduinoServo(10, 180);
            Gps = new Implementations::Gps::UbloxGpsI2c(&Wire, 66);
            Magnetometer = new Implementations::Magnetometers::SparkFunICM20948(&Wire, 68, tiltCompensatedCompassSettings);
            WindSensor = new Implementations::WindSensors::AnalogWindSensorWithMagnetometerCorrection(A0, Magnetometer);
        }

        static void Update() {
            Gps->Update();
            Magnetometer->Update();
            WindSensor->Update();
        }
    };
}
