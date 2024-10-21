#ifndef GPSBASE_H
#define GPSBASE_H

namespace Electronics::Types {
    enum class GpsFix {
        NoFix,
        Fix,
    };

    class GpsBase {
    public:
        virtual ~GpsBase() = default;
        virtual GpsFix Update() = 0;
        virtual double GetLatitude() = 0;
        virtual double GetLongitude() = 0;
        virtual double GetSpeed() = 0;
    };
}


#endif
