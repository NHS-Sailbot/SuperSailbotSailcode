/// Created by Computery on 11/8/2024.

#include "LimitSwitchBase.h"
namespace Electronics::Types {
    LimitSwitchBase::~LimitSwitchBase() {
        LimitSwitches.erase(std::remove(LimitSwitches.begin(), LimitSwitches.end(), this), LimitSwitches.end());
    }

    LimitSwitchBase::LimitSwitchBase(uint8_t limitPin) {
        LimitSwitches.push_back(this);
        m_LimitPin = limitPin;
        pinMode(m_LimitPin, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(m_LimitPin), staticLimitHit, FALLING);
    }

    void LimitSwitchBase::staticLimitHit() {
        for (LimitSwitchBase *limitSwitch: LimitSwitches) {
            if (digitalRead(limitSwitch->m_LimitPin) == LOW) {
                limitSwitch->LimitHit();
            }
        }
    }
}
