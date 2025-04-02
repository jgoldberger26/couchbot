#include <stdbool.h>

enum Side {
    LEFT,
    RIGHT
};

enum Speed {
    LOW_SPEED,
    MEDIUM_SPEED,
    HIGH_SPEED
};

int set_reverse(bool reverse);
int set_throttle(float throttle, enum Side side);
int set_speed(enum Speed speed, enum Side side);
int set_brake_switch(bool brake, enum Side side);
// int set_brake_analog(float percent, enum Side side);