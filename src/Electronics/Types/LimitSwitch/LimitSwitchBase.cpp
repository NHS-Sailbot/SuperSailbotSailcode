/// Created by Computery on 11/8/2024.

#include "LimitSwitchBase.h"

#include "Logging/Logger.h"

using namespace Logging;

namespace Electronics::Types {
    LimitSwitchBase::~LimitSwitchBase() {
        LimitSwitches.erase(std::remove(LimitSwitches.begin(), LimitSwitches.end(), this), LimitSwitches.end());
    }

    LimitSwitchBase::LimitSwitchBase(uint8_t limitPin) {
        Logger::Log(F("Limit switch created!"));
        LimitSwitches.push_back(this);
        m_LimitPin = limitPin;
        pinMode(m_LimitPin, INPUT_PULLUP);
        m_LastPinState = digitalRead(m_LimitPin);
        attachInterrupt(digitalPinToInterrupt(m_LimitPin), staticLimitHit, CHANGE);
    }

    bool LimitSwitchBase::IsPressed() const {
        return digitalRead(m_LimitPin) == LOW;
    }

    bool LimitSwitchBase::IsOpen() const {
        return digitalRead(m_LimitPin) == HIGH;
    }

    void LimitSwitchBase::staticLimitHit() {
        for (LimitSwitchBase* limitSwitch : LimitSwitches) {
            const int currentState = digitalRead(limitSwitch->m_LimitPin);
            if (currentState == limitSwitch->m_LastPinState) {
                continue;
            }

            if (currentState == LOW) {
                limitSwitch->LimitHit();
            }

            limitSwitch->m_LastPinState = currentState;
        }
    }
}
