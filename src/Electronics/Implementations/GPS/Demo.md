# Implementing the `GpsBase` Pure Virtual Class

Your goal is to implement the `GpsBase` class, which is a pure
virtual class that defines the interface for a GPS device. 
The `GpsBase` class is defined in the `Electronics::Types` namespace.

## GpsBase Class Overview

The `GpsBase` class, defined in the `Electronics::Types` namespace, declares the following pure virtual methods:

- `GpsFix Update()`: Updates the state of the GPS device and returns the fix status (either `NoFix` or `Fix`).
- `GpsFix GetFix()`: Returns the current fix of the GPS device.
- `double GetLatitude()`: Returns the latitude value of the GPS device.
- `double GetLongitude()`: Returns the longitude value of the GPS device.
- `double GetSpeed()`: Returns the speed of the GPS device.

We will implement all of these methods in the `GpsDevice` class.

## Goal

Have two working implementations of the `GpsBase` class,
one using the I2C interface and the other using the Serial interface by the end
of the class. One person works on the I2C implementation and the other person works
on the Serial implementation.

## Creating the Gps Implementation Header File

For this we will be working entirely within a header file as it is a simple.
Create a new class named `UBloxGPSIC2.h` or `UBloxGPSSerial.h` depending on the
interface assigned to you in the `src/Electronics/Implementations/GPS` directory,
then delete the cpp file.

## Implementing the GpsBase Class
paste the following code into the header file you created 
(Do not remove the directives at the top and bottom of the file):

```cpp
#include "Electronics/Types/GpsBase.h"

using namespace Electronics::Types;

class CLASSNAMEHERE : GpsBase {
public:
    void Init() {
        // Add any initialization code here
    }

    GpsFix Update() override {
        // Add any update code here and return the fix status
    }
    
    GpsFix GetFix() override {
        // Return the fix status
    }
    
    double GetLatitude() override {
        // Return the latitude
    }
    
    double GetLongitude() override {
        // Return the longitude
    }
    
    double GetSpeed() override {
        // Return the calculated speed (stretch goal)
    }
    
private:
    // Add any private variables here
};
```

replace `CLASSNAMEHERE` with `UBloxGPSIC2` or `UBloxGPSSerial` depending on the interface assigned to you.

## Implementing the GpsBase Class
Take a look at the [Ublox GPS Library](https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library)
and implement the methods in the `GpsBase` class so they return the 
expected values. The Library is already included in the 
project so you can use it. Ask as many questions as you need to get this done.

