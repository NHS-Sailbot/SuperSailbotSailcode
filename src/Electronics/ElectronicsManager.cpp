/// Created by Computery on 11/8/2024.

#include "ElectronicsManager.h"

#include <Wire.h>
#include "Implementations/GPS/UBlox/UbloxGpsI2c.h"
#include "Implementations/LimitSwitches/InterruptLimitSwitchWithCallbacks.h"
#include "Implementations/Magnetometers/SparkFunICM20948.h"
#include "Implementations/Servos/ArduinoServo.h"
#include "Logging/Logger.h"
#include <ArduinoJson.h>
#include "Implementations/WindSensors/FancyWindSensor.h"

using namespace Electronics::Implementations;
using namespace Logging;

namespace Electronics {
    void ElectronicsManager::Start() {
        Logger::Log(F("Starting electronics..."));

        Wire1.begin();
        Wire1.setClock(400000);
        
        Wire.begin();
        Wire.setClock(400000);

        WinchServo = new Servos::ArduinoServo(9, 1080);
        MinLimitSwitchWinch = new InterruptLimitSwitchWithCallbacks(2);
        MaxLimitSwitchWinch = new InterruptLimitSwitchWithCallbacks(3);
        JibWinchServo = new Servos::ArduinoServo(11, 180);
        RudderServo = new Servos::ArduinoServo(10, 180);

        Gps = new Gps::UbloxGpsI2c(Wire1, 0x42);

        Magnetometer = new Magnetometers::SparkFunICM20948(
            Types::TiltCompensatedCompassSettings{
                .A_B = { 79.60,  -18.56,  383.31 },
                .A_Ainv = {
                    { 1.00847, 0.00470, -0.00428 },
                    { 0.00470, 1.00846, -0.00328 },
                    { -0.00428, -0.00328, 0.99559 }
                },
                
                .M_B = { -156.70, -52.79, -141.07 },
                .M_Ainv = {
                    { 1.12823, -0.01142, 0.00980 },
                    { -0.01142, 1.09539, 0.00927 },
                    { 0.00980, 0.00927, 1.10625 }
                },

                .declination = 14.84,

                .facingVector = {1.0f, 0.0f, 0.0f}
            }, Wire1, 0x68);

        WindSensor = new WindSensors::FancyWindSensor(Magnetometer, 0.0,Wire);


        Logger::Log(F("Electronics started!"));
    }

    void ElectronicsManager::Update() {
        Gps->Update();
        WindSensor->Update();
        Magnetometer->Update();

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

        serializeJson(doc, SerialManager::GetSerial());
        SerialManager::GetSerial().println();
    }
}
