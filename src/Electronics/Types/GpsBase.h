#ifndef GPSBASE_H
#define GPSBASE_H
#include "Electronic.h"

namespace Electronics::Types {
    enum class GpsFix {
        NoFix,
        Fix,
    };

    class GpsBase : public Electronics {
    public:
        virtual ~GpsBase() = default;
        virtual void Init() = 0;
        virtual GpsFix Update() = 0;
        virtual GpsFix GetFix() = 0;
        virtual double GetLatitude() = 0;
        virtual double GetLongitude() = 0;
        virtual double GetSpeed() = 0;
    };
}


#endif
