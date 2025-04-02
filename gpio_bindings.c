#include "gpio_bindings.h"
#include <pigpio.h>

#define THROTTLE_PIN_L 6
#define THROTTLE_PIN_R 6
#define REVERSE_PIN_L 6
#define REVERSE_PIN_R 6
#define BRAKE_PIN_L 6
#define BRAKE_PIN_R 6
#define HIGH_SPEED_PIN_L 6
#define HIGH_SPEED_PIN_R 6
#define LOW_SPEED_PIN_L 6
#define LOW_SPEED_PIN_R 6

#define THROTTLE_I2C_ADDR_L 0xde
#define THROTTLE_I2C_ADDR_R 0xad

#define BRAKE_I2C_ADDR_L 0xbe
#define BRAKE_I2C_ADDR_R 0xef

#define I2C_BUS 0

int throttle_i2c_handle_l;
int throttle_i2c_handle_r;
int brake_i2c_handle_l;
int brake_i2c_handle_r;


int init_pins() {
    if (gpioInitialise() < 0) {
        // Failed, return an error
        return -1;
    }

    gpioSetMode(THROTTLE_PIN_L, PI_OUTPUT);
    // For all pins

    throttle_i2c_handle_l = i2cOpen(I2C_BUS, THROTTLE_I2C_ADDR_L, 0);
    brake_i2c_handle_r = i2cOpen(I2C_BUS, BRAKE_I2C_ADDR_L, 0);
}

int shutdown() {
    // For all i2cs
    i2cClose(throttle_i2c_handle_l);
    i2cClose(throttle_i2c_handle_r);
    i2cClose(brake_i2c_handle_l);
    i2cClose(brake_i2c_handle_r);
}

int _set_reverse_r(bool reverse) {
    int err = gpioWrite(REVERSE_PIN_R, !reverse) < 0;
    if (err < 0) {
        if (err == PI_BAD_GPIO) {
            // Handle error
            return -1;
        }
        else if (err == PI_BAD_LEVEL) {
            // Handle error
            return -1;
        }
    }
    return 0;
}
int _set_reverse_l(bool reverse) {
    int err = gpioWrite(REVERSE_PIN_L, !reverse) < 0;
    if (err < 0) {
        if (err == PI_BAD_GPIO) {
            // Handle error
            return -1;
        }
        else if (err == PI_BAD_LEVEL) {
            // Handle error
            return -1;
        }
    }
    return 0;
}

int setReverse(bool reverse, enum Side side) {
    if (side == LEFT) {
        _set_reverse_l(reverse);
    } if (side == RIGHT) {
        _set_reverse_r(reverse);
    }
}

int _set_speed(enum Speed speed, float hi_speed_pin, float lo_speed_pin) {
    int err_hi = 0;
    int err_lo = 0;
    switch (speed)
    {
    case HIGH_SPEED:
        err_hi = gpioWrite(hi_speed_pin, PI_LOW);
        err_lo = gpioWrite(lo_speed_pin, PI_HIGH);
        break;
    case LOW_SPEED:
        err_hi = gpioWrite(hi_speed_pin, PI_HIGH);
        err_lo = gpioWrite(lo_speed_pin, PI_LOW);
        break;
    case MEDIUM_SPEED:
        err_hi = gpioWrite(hi_speed_pin, PI_HIGH);
        err_lo = gpioWrite(lo_speed_pin, PI_HIGH);
        break;
    default:
        
        break;
    }

    if (err_hi < 0) {
        // Handle error
        return -1;
    }
    if (err_lo < 0) {
        // Handle error
        return -1;
    }

    return 0;
}

int set_speed(enum Speed speed, enum Side side) {
    switch (side) {
        case LEFT:
            return _set_speed(speed, HIGH_SPEED_PIN_L, LOW_SPEED_PIN_L);
        case RIGHT:
            return _set_speed(speed, HIGH_SPEED_PIN_R, LOW_SPEED_PIN_R);
        default:
            return -1; // Different error
    }
}

int _set_brake_switch(bool brake, uint8_t pin) {
    int err = gpioWrite(pin, !brake) < 0;
    if (err < 0) {
        if (err == PI_BAD_GPIO) {
            // Handle error
            return -1;
        }
        else if (err == PI_BAD_LEVEL) {
            // Handle error
            return -1;
        }
    }
    return 0;
}

int set_brake_switch(bool brake, enum Side side) {
    switch (side) {
        case LEFT:
            return _set_brake_switch(brake, BRAKE_PIN_R);
        case RIGHT:
            return _set_brake_switch(brake, BRAKE_PIN_L);
    }
}

int write_fast_mode(uint8_t handle, uint16_t bytes) {
    // Zero power down bits and cc bits
    bytes &= 0x0fff;
    // TODO actually handle errors
    return i2cWriteByteData(handle, bytes >> 8, bytes & 0xFF);
}

int write_percent_to_i2c(uint8_t handle, float percent) {
    uint16_t input_code = percent * 4096; // 12 bits
    return write_fast_mode(handle, input_code);
}

int set_throttle(float percent, enum Side side) {
    switch (side)
    {
    case LEFT:
        return write_fast_mode(throttle_i2c_handle_l, percent);
    case RIGHT:
        return write_fast_mode(throttle_i2c_handle_r, percent);
    default:
        return -1;
    }
}

int set_brake_analog(float percent, enum Side side) {
    // Not implemented
    exit(-1);
}