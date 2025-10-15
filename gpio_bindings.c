#include "gpio_bindings.h"
#include <wiringPi.h> //TODO move everything to this!
#include <wiringPiI2C.h>
#include <unistd.h>

#define THROTTLE_PIN_L 6
#define THROTTLE_PIN_R 6
#define REVERSE_PIN_L 22
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

#define LOW 0
#define HIGH 1

int throttle_i2c_handle_l;
int throttle_i2c_handle_r;
int brake_i2c_handle_l;
int brake_i2c_handle_r;


int init_pins() {
    if (wiringPiSetupPinType(WPI_PIN_BCM) < 0) {
        // Failed, return an error
        return -1;
    }

    pinMode(THROTTLE_PIN_L, OUTPUT);
    // For all pins

    throttle_i2c_handle_l = wiringPiI2CSetup(THROTTLE_I2C_ADDR_L);
    throttle_i2c_handle_r = wiringPiI2CSetup(THROTTLE_I2C_ADDR_R);


    brake_i2c_handle_r = wiringPiI2CSetup(BRAKE_I2C_ADDR_R);
    brake_i2c_handle_l = wiringPiI2CSetup(BRAKE_I2C_ADDR_L);

    return 0;
}

int shutdown() {
    // For all i2cs
    close(throttle_i2c_handle_l);
    close(throttle_i2c_handle_r);
    close(brake_i2c_handle_l);
    close(brake_i2c_handle_r);
    return 0;
}

int _set_reverse_r(bool reverse) {
    digitalWrite(REVERSE_PIN_R, !reverse);
    return 0;
}
int _set_reverse_l(bool reverse) {
    digitalWrite(REVERSE_PIN_L, !reverse);
    return 0;
}

void setReverse(bool reverse, enum Side side) {
    if (side == LEFT) {
        _set_reverse_l(reverse);
    } if (side == RIGHT) {
        _set_reverse_r(reverse);
    }
}

int _set_speed(enum Speed speed, float hi_speed_pin, float lo_speed_pin) {
    switch (speed)
    {
    case HIGH_SPEED:
        digitalWrite(hi_speed_pin, LOW);
        digitalWrite(lo_speed_pin, HIGH);
        break;
    case LOW_SPEED:
        digitalWrite(hi_speed_pin, HIGH);
        digitalWrite(lo_speed_pin, LOW);
        break;
    case MEDIUM_SPEED:
        digitalWrite(hi_speed_pin, HIGH);
        digitalWrite(lo_speed_pin, HIGH);
        break;
    default:
        break;
    }


    return 0;
}

void set_speed(enum Speed speed, enum Side side) {
    switch (side) {
        case LEFT:
             _set_speed(speed, HIGH_SPEED_PIN_L, LOW_SPEED_PIN_L);
        case RIGHT:
             _set_speed(speed, HIGH_SPEED_PIN_R, LOW_SPEED_PIN_R);
    }
}

void _set_brake_switch(bool brake, uint8_t pin) {
    digitalWrite(pin, !brake);
}

void set_brake_switch(bool brake, enum Side side) {
    switch (side) {
        case LEFT:
            _set_brake_switch(brake, BRAKE_PIN_R);
        case RIGHT:
            _set_brake_switch(brake, BRAKE_PIN_L);
    }
}

int write_fast_mode(uint8_t handle, uint16_t bytes) {
    // Zero power down bits and cc bits
    bytes &= 0x0fff;
    // TODO actually handle errors
    return wiringPiI2CWriteReg8(handle, bytes >> 8, bytes & 0xFF);
}

int write_percent_to_i2c(uint8_t handle, float percent) {
    uint16_t input_code = percent * 4096; // 12 bits
    return write_fast_mode(handle, input_code);
}

void set_throttle(float percent, enum Side side) {
    switch (side)
    {
    case LEFT:
        write_fast_mode(throttle_i2c_handle_l, percent);
    case RIGHT:
        write_fast_mode(throttle_i2c_handle_r, percent);
    }
}

int set_brake_analog(float percent, enum Side side) {
    // Not implemented
    // exit(-1);
    return -1;
}

