/// Created by Computery on 3/15/2025.

#pragma once

#include <Arduino.h>

class LEDStuff {
public:
    static void Start(){
        pinMode(D88, OUTPUT); // Blue
        pinMode(D86, OUTPUT); // Red
        pinMode(D87, OUTPUT); // GREEN
    }

    static void SetRGB(bool r, bool g, bool b) {
        digitalWrite(D86, r ? LOW : HIGH); // Red
        digitalWrite(D87, g ? LOW : HIGH); // Green
        digitalWrite(D88, b ? LOW : HIGH); // Blue
    }
};