// https://cnkunray.com/products/kunray-krbc-15mos-48v-60v-2000w-33a-brushless-motor-speed-controller-for-electric-bicycle-scooter?VariantsId=10170

#include "utils.h"
#include <wiringPi.h> 

// The KRBC-15MOS motor controller
class KRBC_15MOS {
    private:
        int throttle_handle;        // The throttle for the controller, W, red/white/black
        int brake_handle;           // The brake for the controller, W, purple/black
        int three_speed_handle;     // The gear ratio for the controller, W, blue/black/yellow
        int e_lock_handle;          // The lock for the controller, W, red/orange
        int indicator_light_handle; // (I dont' know what this actually indicates), R, orange/black
        int brake_light_handle;     // Indicates braking, R, pink/purple
        int charge_handle;          // (Unknown), (Unknown), red/black

        int reverse_pin;         // The reverse for the controller, W, brown/black

    public:
        KRBC_15MOS(Motor_Config config) {
            throttle_handle = config.handles["throttle"];
            brake_handle = config.handles["brake"];
            three_speed_handle = config.handles["three_speed"];
            e_lock_handle = config.handles["e_lock"];
            indicator_light_handle = config.handles["indicator_light"];
            brake_light_handle = config.handles["brake_light"];
            charge_handle = config.handles["charge"];

            reverse_pin = config.pins["reverse"];
            pinMode(reverse_pin, OUTPUT);
        }
        void reverse(bool reverse);
        void throttle(float percent);
        void setSpeed(Speed speed);
        void brake(bool brake);
};

void KRBC_15MOS::reverse(bool reverse) {
    digitalWrite(reverse_pin, !reverse);
}