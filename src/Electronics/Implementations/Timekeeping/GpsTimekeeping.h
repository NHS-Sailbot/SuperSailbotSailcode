#pragma once

#include <Arduino.h>
#include "Constants.h"
#include "Electronics/Types/Gps/GpsBase.h"
#include "Electronics/Types/Timekeeping/TimekeepingBase.h"

namespace Electronics::Implementations::Timekeeping {
    class GpsTimekeeping final : public Types::TimekeepingBase {
    public:
        explicit GpsTimekeeping(Types::GpsBase* gps) : m_Gps(gps) {}

        void Update() override {
            SyncGpsAnchor();

            const unsigned long nowMs = millis();

            for (auto& entry : m_DelayCallbacks) {
                if (!entry.active) {
                    continue;
                }

                if (static_cast<long>(nowMs - entry.fireAtMs) >= 0) {
                    entry.callback();
                    ClearDelayEntry(entry);
                }
            }

            if (m_HasGpsAnchor) {
                const Types::UtcTime now = GetCurrentUtc();

                for (auto& entry : m_TimeCallbacks) {
                    if (!entry.active) {
                        continue;
                    }

                    if (Types::CompareUtc(now, entry.target) >= 0) {
                        entry.callback();
                        ClearTimeEntry(entry);
                    }
                }
            }
        }

        bool HasValidUtc() const override {
            return m_HasGpsAnchor;
        }

        Types::UtcTime GetCurrentUtc() const override {
            if (!m_HasGpsAnchor) {
                return {};
            }

            return Types::AddMilliseconds(m_GpsAnchorUtc, millis() - m_GpsAnchorMillis);
        }

        /// Cannot exceed Constants::MAX_DELAY_CALLBACKS active callbacks; returns -1 when full.
        int RegisterDelayCallback(const std::function<void()>& callback, const unsigned long delayMs) override {
            for (auto& entry : m_DelayCallbacks) {
                if (entry.active) {
                    continue;
                }

                entry.active = true;
                entry.id = m_NextId++;
                entry.callback = callback;
                entry.fireAtMs = millis() + delayMs;
                return entry.id;
            }

            return -1;
        }

        /// Cannot exceed Constants::MAX_TIME_CALLBACKS active callbacks; returns -1 when full.
        int RegisterTimeCallback(const std::function<void()>& callback, const Types::UtcTime target) override {
            for (auto& entry : m_TimeCallbacks) {
                if (entry.active) {
                    continue;
                }

                entry.active = true;
                entry.id = m_NextId++;
                entry.callback = callback;
                entry.target = target;
                return entry.id;
            }

            return -1;
        }

        bool DeregisterCallback(const int id) override {
            for (auto& entry : m_DelayCallbacks) {
                if (entry.active && entry.id == id) {
                    ClearDelayEntry(entry);
                    return true;
                }
            }

            for (auto& entry : m_TimeCallbacks) {
                if (entry.active && entry.id == id) {
                    ClearTimeEntry(entry);
                    return true;
                }
            }

            return false;
        }

    private:
        struct DelayEntry {
            bool active = false;
            int id = -1;
            std::function<void()> callback;
            unsigned long fireAtMs = 0;
        };

        struct TimeEntry {
            bool active = false;
            int id = -1;
            std::function<void()> callback;
            Types::UtcTime target;
        };

        static void ClearDelayEntry(DelayEntry& entry) {
            entry.active = false;
            entry.id = -1;
            entry.callback = nullptr;
            entry.fireAtMs = 0;
        }

        static void ClearTimeEntry(TimeEntry& entry) {
            entry.active = false;
            entry.id = -1;
            entry.callback = nullptr;
            entry.target = {};
        }

        Types::UtcTime GetUtcFromGps() const {
            return {
                m_Gps->GetYear(),
                m_Gps->GetMonth(),
                m_Gps->GetDay(),
                m_Gps->GetHour(),
                m_Gps->GetMinute(),
                m_Gps->GetSecond(),
                m_Gps->GetMillisecond(),
            };
        }

        void SyncGpsAnchor() {
            if (m_Gps == nullptr || !m_Gps->IsTimeValid() || !m_Gps->IsDateValid()) {
                return;
            }

            m_GpsAnchorUtc = GetUtcFromGps();
            m_GpsAnchorMillis = millis();
            m_HasGpsAnchor = true;
        }

        Types::GpsBase* m_Gps;
        int m_NextId = 0;
        DelayEntry m_DelayCallbacks[Constants::MAX_DELAY_CALLBACKS] = {};
        TimeEntry m_TimeCallbacks[Constants::MAX_TIME_CALLBACKS] = {};

        Types::UtcTime m_GpsAnchorUtc;
        unsigned long m_GpsAnchorMillis = 0;
        bool m_HasGpsAnchor = false;
    };
}
