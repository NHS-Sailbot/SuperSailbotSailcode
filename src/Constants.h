/// Created by Computery on 6/7/2025.

#pragma once

#include <cstddef>

namespace Constants {
    /// Radius of Earth in meters.
    inline constexpr long RADIUS_OF_EARTH = 6371000;

    /// A complete rotation in degrees.
    static constexpr double FULL_CIRCLE = 360.0;

    /// Max concurrent delay callbacks per timekeeping implementation. Cannot register more than this.
    inline constexpr size_t MAX_DELAY_CALLBACKS = 8;

    /// Max concurrent UTC time callbacks per timekeeping implementation. Cannot register more than this.
    inline constexpr size_t MAX_TIME_CALLBACKS = 8;

    /// Max concurrent callbacks per limit switch implementation. Cannot register more than this.
    inline constexpr size_t MAX_LIMIT_SWITCH_CALLBACKS = 8;
}
