#pragma once

#include <Arduino.h>

namespace Electronics::Types {
    struct UtcTime {
        uint16_t year = 0;
        uint8_t month = 0;
        uint8_t day = 0;
        uint8_t hour = 0;
        uint8_t minute = 0;
        uint8_t second = 0;
        uint16_t millisecond = 0;
    };

    // bullshit that won't ever come up but like it's technically the best thing to do
    inline bool IsLeapYear(const uint16_t year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    inline uint8_t DaysInMonth(const uint16_t year, const uint8_t month) {
        static constexpr uint8_t days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // fuck ass
        if (month < 1 || month > 12) { return 31; }
        if (month == 2 && IsLeapYear(year)) { return 29; }
        return days[month - 1];
    }

    inline void AdvanceDays(UtcTime& time, uint32_t days) {
        while (days > 0) {
            const uint8_t daysInMonth = DaysInMonth(time.year, time.month);
            const uint32_t daysLeftInMonth = static_cast<uint32_t>(daysInMonth - time.day + 1);

            if (days < daysLeftInMonth) {
                time.day = static_cast<uint8_t>(time.day + days);
                return;
            }

            days -= daysLeftInMonth;
            time.day = 1;
            time.month++;
            if (time.month > 12) {
                time.month = 1;
                time.year++;
            }
        }
    }

    inline UtcTime AddMilliseconds(UtcTime time, const unsigned long ms) {
        const uint64_t totalMs = static_cast<uint64_t>(time.millisecond) + static_cast<uint64_t>(ms);
        time.millisecond = static_cast<uint16_t>(totalMs % 1000u);

        const uint64_t totalSecondsInDay =
            static_cast<uint64_t>(time.hour) * 3600u +
            static_cast<uint64_t>(time.minute) * 60u +
            static_cast<uint64_t>(time.second) +
            totalMs / 1000u;

        const uint32_t daysToAdd = static_cast<uint32_t>(totalSecondsInDay / 86400u);
        const uint32_t secondsInDay = static_cast<uint32_t>(totalSecondsInDay % 86400u);

        if (daysToAdd > 0) {
            AdvanceDays(time, daysToAdd);
        }

        time.hour = static_cast<uint8_t>(secondsInDay / 3600u);
        time.minute = static_cast<uint8_t>((secondsInDay / 60u) % 60u);
        time.second = static_cast<uint8_t>(secondsInDay % 60u);
        return time;
    }

    /// Returns negative if a < b, zero if equal, positive if a > b.
    inline int CompareUtc(const UtcTime& a, const UtcTime& b) {
        if (a.year != b.year) { return a.year < b.year ? -1 : 1; }
        if (a.month != b.month) { return a.month < b.month ? -1 : 1; }
        if (a.day != b.day) { return a.day < b.day ? -1 : 1; }
        if (a.hour != b.hour) { return a.hour < b.hour ? -1 : 1; }
        if (a.minute != b.minute) { return a.minute < b.minute ? -1 : 1; }
        if (a.second != b.second) { return a.second < b.second ? -1 : 1; }
        if (a.millisecond != b.millisecond) { return a.millisecond < b.millisecond ? -1 : 1; }
        return 0;
    }
}
