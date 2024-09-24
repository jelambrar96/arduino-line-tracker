#include "motors.h"

Motor::Motor(unsigned char enA, unsigned char in1, char in2) {
    enA = enA;
    in1 = in1;
    in2 = in2;
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
}

Motor::~Motor() {}

unsigned int Motor::getSpeed() {
    return speed;
}

void Motor::setSpeed(unsigned int spd) {
    speed = spd;
}

void Motor::forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, speed);
}

void Motor::backward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, speed);
}
