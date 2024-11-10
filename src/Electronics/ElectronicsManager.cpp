/// Created by Computery on 11/8/2024.

#include "ElectronicsManager.h"

#include <Wire.h>
#include "Implementations/GPS/UBlox/UbloxGpsI2c.h"
#include "Implementations/LimitSwitches/InterruptLimitSwitchMethod.h"
#include "Implementations/Magnetometers/SparkFunICM20948.h"
#include "Implementations/Servos/ArduinoServo.h"
#include "Implementations/WindSensors/AnalogWindSensorWithMagnetometerCorrection.h"
#include "Logging/Logger.h"

using namespace Electronics::Implementations;
using namespace Logging;

namespace Electronics {
    void ElectronicsManager::Start() {
        Logger::Log(F("Starting electronics..."));

        Wire.begin();
        Wire.setClock(400000);

        WinchServo = new Servos::ArduinoServo(9, 1080);
        MinLimitSwitchWinch = new InterruptLimitSwitchMethod(2, [] {});
        MaxLimitSwitchWinch = new InterruptLimitSwitchMethod(3, [] {});
        JibWinchServo = new Servos::ArduinoServo(11, 180);
        RudderServo = new Servos::ArduinoServo(10, 180);

        Gps = new Gps::UbloxGpsI2c(&Wire, 66);

        Magnetometer = new Magnetometers::SparkFunICM20948(&Wire, 68, {
            { 79.60,  -18.56,  383.31 },
            {
                { 1.00847, 0.00470, -0.00428 },
                { 0.00470, 1.00846, -0.00328 },
                { -0.00428, -0.00328, 0.99559 }
            },
            { -156.70, -52.79, -141.07 },
            {
                { 1.12823, -0.01142, 0.00980 },
                { -0.01142, 1.09539, 0.00927 },
                { 0.00980, 0.00927, 1.10625 }
            },
            14.84,
            {1.0f, 0.0f, 0.0f}
        });

        WindSensor = new WindSensors::AnalogWindSensorWithMagnetometerCorrection(A0, Magnetometer);

        Logger::Log(F("Electronics started!"));
    }

    void ElectronicsManager::Update() {
        Gps->Update();
        WindSensor->Update();
        Magnetometer->Update();
    }
}
