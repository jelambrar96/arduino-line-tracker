#ifndef MOTORS_HPP
#define MOTORS_HPP

#include <Arduino.h>

class Motor {
public:
    Motor(unsigned char enA, unsigned char in1, char in2);
    ~Motor();
    void setSpeed(unsigned int spd);
    void forward();
    void backward();

private:
    unsigned int speed = 0;
    unsigned char enA;
    unsigned char in1;
    unsigned char in2;
};

#endif