#include "motors.h"

Motor::Motor(unsigned char enA, unsigned char in1, char in2) {
    _enA = enA;
    _in1 = in1;
    _in2 = in2;
    pinMode(_enA, OUTPUT);
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
}

Motor::~Motor() {}

unsigned char Motor::getSpeed() {
    return speed;
}

void Motor::setSpeed(unsigned char spd) {
    speed = spd;
}

void Motor::forward() {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    analogWrite(_enA, speed);
}

void Motor::backward() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    analogWrite(_enA, speed);
}

void Motor::stop() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    analogWrite(_enA, speed);    
}
