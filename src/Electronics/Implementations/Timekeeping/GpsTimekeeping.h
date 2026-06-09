#pragma once

#include <Arduino.h>
#include "Electronics/Types/Gps/GpsBase.h"
#include "Electronics/Types/Timekeeping/TimekeepingBase.h"
#include <vector>

namespace Electronics::Implementations::Timekeeping {
    class GpsTimekeeping final : public Types::TimekeepingBase {
    public:
        explicit GpsTimekeeping(Types::GpsBase* gps) : m_Gps(gps) {}

        void Update() override {
            SyncGpsAnchor();

            const unsigned long nowMs = millis();

            for (auto it = m_DelayCallbacks.begin(); it != m_DelayCallbacks.end(); ) {
                if (static_cast<long>(nowMs - it->fireAtMs) >= 0) {
                    it->callback();
                    it = m_DelayCallbacks.erase(it);
                } else {
                    ++it;
                }
            }

            if (m_HasGpsAnchor) {
                const Types::UtcTime now = GetCurrentUtc();

                for (auto it = m_TimeCallbacks.begin(); it != m_TimeCallbacks.end(); ) {
                    if (Types::CompareUtc(now, it->target) >= 0) {
                        it->callback();
                        it = m_TimeCallbacks.erase(it);
                    } else {
                        ++it;
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

        int RegisterDelayCallback(const std::function<void()>& callback, const unsigned long delayMs) override {
            const int id = m_NextId++;
            m_DelayCallbacks.push_back({ id, callback, millis() + delayMs });
            return id;
        }

        int RegisterTimeCallback(const std::function<void()>& callback, const Types::UtcTime target) override {
            const int id = m_NextId++;
            m_TimeCallbacks.push_back({ id, callback, target });
            return id;
        }

        bool DeregisterCallback(const int id) override {
            for (auto it = m_DelayCallbacks.begin(); it != m_DelayCallbacks.end(); ++it) {
                if (it->id == id) {
                    m_DelayCallbacks.erase(it);
                    return true;
                }
            }

            for (auto it = m_TimeCallbacks.begin(); it != m_TimeCallbacks.end(); ++it) {
                if (it->id == id) {
                    m_TimeCallbacks.erase(it);
                    return true;
                }
            }

            return false;
        }

    private:
        struct DelayEntry {
            int id;
            std::function<void()> callback;
            unsigned long fireAtMs;
        };

        struct TimeEntry {
            int id;
            std::function<void()> callback;
            Types::UtcTime target;
        };

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
        std::vector<DelayEntry> m_DelayCallbacks;
        std::vector<TimeEntry> m_TimeCallbacks;

        Types::UtcTime m_GpsAnchorUtc;
        unsigned long m_GpsAnchorMillis = 0;
        bool m_HasGpsAnchor = false;
    };
}
