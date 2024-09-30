#ifndef MOTORS_HPP
#define MOTORS_HPP

#include <Arduino.h>

class Motor {
public:
    Motor(unsigned char enA, unsigned char in1, char in2);
    ~Motor();
    unsigned char getSpeed();
    void setSpeed(unsigned char spd);
    void forward();
    void backward();
    void stop();

protected:
    unsigned char speed = 0;
    unsigned char _enA;
    unsigned char _in1;
    unsigned char _in2;
};


#endif
