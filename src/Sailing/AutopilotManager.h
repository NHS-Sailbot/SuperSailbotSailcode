/// Created by Computery on 11/8/2024.

#pragma once
#include "Types/AutopilotBase.h"

namespace Sailing {
    class AutopilotManager {
    public:
        static void Start();
        static void Update();
    private:
        inline static AutopilotBase *m_Autopilot = nullptr;
    };
}
