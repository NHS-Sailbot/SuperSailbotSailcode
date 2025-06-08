/// Created by Computery on 11/9/2024.

#pragma once

namespace Sailing::Types {
    class AutopilotBase {
    public:
        virtual ~AutopilotBase() = default;
        
        /// Updates the autopilot
        virtual void Update() = 0;
    };
}
