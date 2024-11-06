/// Created by Computery on 11/5/2024.

#pragma once

#include "Electronics/Types/Gps/UbloxGpsBase.h"
#include <HardwareSerial.h>

namespace Electronics::Implementations::Gps {
    class UbloxGpsSerial final : public Types::UbloxGpsBase {
    public:
        explicit UbloxGpsSerial(arduino::HardwareSerial* serialPort);
    };
}
