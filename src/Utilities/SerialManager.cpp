/// Created by Computery on 3/15/2025.

#include "SerialManager.h"
#include "LEDStuff.h"
#include "Logging/Logger.h"

void SerialManager::Start(const SerialSettings settings) {
    if (HasStarted) { return; }
    
    Settings = settings;
    Settings.serial->setTimeout(5000); // Set a timeout for serial reads
    Settings.serial->begin(settings.baudRate);
    Settings.serial->flush();
    
    HasStarted = true;

    RegisterCallback(IdentifyDevice, 255); // Register a callback for the unique identifier
}

void SerialManager::IdentifyDevice() {
    int x = 80085;
    const char* bytes = static_cast<char*>(static_cast<void*>(&x));

    LEDStuff::SetRGB(true, false, false); // Set LED to red for identification
    GetSerial().write(bytes, 4); // Send the unique identifier
    delay(5000); // Wait for 5 seconds to allow the receiving end to process the identifier
    LEDStuff::SetRGB(false, false, false); // Turn off the LED after identification
    
    FoundApi = true; // Mark that the API has been found
    
    Logging::Logger::Start();
}

HardwareSerial& SerialManager::GetSerial() {
    if (!HasStarted) { Start();} // Ensure Serial is started before returning
    return *Settings.serial;
}

void SerialManager::Update() {
    if (!HasStarted) { Start(); } // Ensure Serial is started before updating
    if (Settings.serial->available()) {
        int peekedType = Settings.serial->peek();
                
        if (callbacks.count(peekedType) > 0) {
            Settings.serial->read(); // CONSUME DATA
            callbacks[peekedType](); // Call the registered callback for the peeked type
        } else {
            Settings.serial->read(); // Read and discard if no callback is registered
        }
    }
}

bool SerialManager::RegisterCallback(const std::function<void()>& callback, const uint8_t index) {
    if (callbacks.find(index) != callbacks.end()) {
        return false; // Callback already exists at this index
    }
    callbacks[index] = callback;
    return true; // Callback registered successfully
}

bool SerialManager::DeregisterCallback(int index) {
    auto it = callbacks.find(index);
    if (it != callbacks.end()) {
        callbacks.erase(it);
        return true; // Callback deregistered successfully
    }
    return false; // No callback found at this index
}
