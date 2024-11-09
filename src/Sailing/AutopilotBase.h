/// Created by Computery on 11/9/2024.

#pragma once

namespace Sailing {
    class AutopilotBase {
    public:
        virtual ~AutopilotBase() = default;

        /// Initializes the autopilot
        virtual void Start() = 0;

        /// Updates the autopilot
        virtual void Update() = 0;
    };
}
