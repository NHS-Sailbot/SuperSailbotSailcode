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
        Magnetometer = new Magnetometers::SparkFunICM20948(&Wire, 68, {});
        WindSensor = new WindSensors::AnalogWindSensorWithMagnetometerCorrection(A0, Magnetometer);

        Logger::Log(F("Electronics started!"));
    }

    void ElectronicsManager::Update() {
        Gps->Update();
        WindSensor->Update();
        Magnetometer->Update();
    }
}
