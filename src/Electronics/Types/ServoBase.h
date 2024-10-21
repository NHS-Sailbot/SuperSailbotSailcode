/// Created by Computery on 9/19/2024.

#ifndef SERVO_H
#define SERVO_H

namespace Electronics::Types {
    class ServoBase {
    public:
        virtual ~ServoBase() = default;

        /// Returns the angle of the servo in degrees
        virtual int GetAngle() = 0;

        /// Sets the angle of the servo in degrees
        virtual void SetAngle(int angle) = 0;
    };
}

#endif
