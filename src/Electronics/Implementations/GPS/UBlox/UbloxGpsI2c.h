/// Created by Computery on 11/5/2024.

#pragma once

#include "UbloxGpsBase.h"

namespace Electronics::Implementations::Gps {
    class UbloxGpsI2c final : public Types::UbloxGpsBase {
    public:
        explicit UbloxGpsI2c(MbedI2C& i2cWire, uint8_t address);
    };
}
