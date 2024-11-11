/// Created by Computery on 11/9/2024.

#pragma once

#include <USBHostMSD/USBHostMSD.h>
#include "Logging/Logger.h"

class FileSystem {
public:
    inline static USBHostMSD msd = USBHostMSD();
    inline static mbed::FATFileSystem usb = mbed::FATFileSystem("usb");
    inline static mbed::DigitalOut otg = mbed::DigitalOut(PB_14);
    inline static bool Started = false;

    static void Start() {
        pinMode(PA_15, OUTPUT);
        digitalWrite(PA_15, HIGH);

        int errorInt =  usb.mount(&msd);
        if (errorInt != 0) {
            Logging::Logger::Log(F("Failed to mount USB, is the USB_NAME constant correct?"));
            return;
        }

        Started = true;
    }

    /// Make sure you handle the returned char array!
    /// Only reads ascii text files.
    /// Returns false when it fails to read the file.
    /// Includes null terminator
    static bool ReadFile(const char* path, char*& outBuffer) {
        if (!Started) {
            Logging::Logger::Log(F("File system not started"));
            return false;
        }

        // Open and check file
        FILE *file = fopen(path, "r+");
        if (file == nullptr) {
            Logging::Logger::Log(F("Failed to open file: " ), false);
            Logging::Logger::Log(path);
            return false;
        }

        fseek(file, 0L, SEEK_END);
        const int length = ftell(file);

        rewind(file);
        outBuffer = new char[length + 1];
        outBuffer[length] = '\0';
        fread(outBuffer, sizeof(char), length, file);

        fflush(stdout); // This is from the example code I don't even know what it does

        int err = fclose(file);
        if (err < 0) {
            Logging::Logger::Log(F("Failed to close file: "), false);
            Logging::Logger::Log(strerror(errno), false);
        }
        return true;
    }
};
