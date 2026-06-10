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
                .A_B = { 5107.72,-7278.80,-7699.62},
                .A_Ainv = {
                    {  0.90144,  0.11881,  0.10734},
                    {  0.11881,  0.83823, -0.13930},
                    {  0.10734, -0.13930,  0.73938}
                },
                .M_B = {  -87.37, -103.67,   39.45},
                .M_Ainv = {
                    {  1.26331, -0.00713, -0.03647},
                    { -0.00713,  1.15732, -0.04364},
                    { -0.03647, -0.04364,  1.21732}
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
