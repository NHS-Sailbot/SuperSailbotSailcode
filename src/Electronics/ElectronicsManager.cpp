/// Created by Computery on 11/8/2024.

#include "ElectronicsManager.h"

#include <Wire.h>
#include "Implementations/GPS/UBlox/UbloxGpsI2c.h"
#include "Implementations/LimitSwitches/InterruptLimitSwitchWithCallbacks.h"
#include "Implementations/Magnetometers/SparkFunICM20948.h"
#include "Implementations/Servos/ArduinoServo.h"
#include "Logging/Logger.h"
#include <ArduinoJson.h>

#include "Implementations/Winches/ServoWinch.h"
#include "Implementations/WindSensors/FancyWindSensor.h"

using namespace Electronics::Implementations;
using namespace Logging;

namespace Electronics {
    void ElectronicsManager::Start() {
        Logger::Log(F("Starting electronics..."));

        Wire1.begin();
        Wire1.setClock(400000);

        WinchServo = new Winches::ServoWinch(*new Servos::ArduinoServo(9, 3600), 1440, 2160);
        MinLimitSwitchWinch = new InterruptLimitSwitchWithCallbacks(2);
        MaxLimitSwitchWinch = new InterruptLimitSwitchWithCallbacks(3);
        JibWinchServo = new Winches::ServoWinch(*new Servos::ArduinoServo(11, 720), 720, 0); // Double check THIS
        RudderServo = new Servos::ArduinoServo(10, 180);

        Gps = new Gps::UbloxGpsI2c(Wire1, 0x42);

        Magnetometer = new Magnetometers::SparkFunICM20948(
            Types::TiltCompensatedCompassSettings{
                .A_B = {  -162.59, -747.85, 3471.47},
                .A_Ainv = {
                    {  1.11294, -0.03751, -0.00642},
                    { -0.03751,  1.09791, -0.03233},
                    { -0.00642, -0.03233,  1.23576}
                },
                .M_B = {  -54.23,  -96.47,   51.07},
                .M_Ainv = {
                    {  1.16150, -0.01453,  0.00732},
                    { -0.01453,  1.12552, -0.05146},
                    {  0.00732, -0.05146,  1.25589}
                },

                .declination = 14.84,

                .facingVector = {1.0f, 0.0f, 0.0f}
            }, Wire1, 0x68);

        WindSensor = new WindSensors::FancyWindSensor(0.0, Serial3, 38400);


        Logger::Log(F("Electronics started!"));
    }

    void ElectronicsManager::Update() {
        Gps->Update();
        Magnetometer->Update();
        WindSensor->Update();

        static unsigned long lastTelemetry = 0;
        if (millis() - lastTelemetry >= 500) {
            lastTelemetry = millis();
            SendTelemetry();
        }
    }

    void ElectronicsManager::SendTelemetry() {
        if (!SerialManager::FoundApi) { return; }
        
        JsonDocument doc;
        doc["type"] = "telemetry";
        doc["gps"]["fix"] = Gps->GetFix();
        doc["gps"]["latitude"] = Gps->GetLatitude();
        doc["gps"]["longitude"] = Gps->GetLongitude();
        doc["gps"]["speed"] = Gps->GetSpeed();
        doc["gps"]["heading"] = Gps->GetHeading();
        doc["magnetometer"]["heading"] = Magnetometer->GetHeading();
        doc["windSensor"]["direction"] = WindSensor->GetDirection();

        Logger::LogJson(doc);
    }
}
