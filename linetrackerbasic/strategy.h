#ifndef STRATEGY_H
#define STRATEGY_H

#include <Arduino.h>


class AbstractStrategy {
public:
    virtual uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) = 0;
};


class MoreInteseStrategy: public AbstractStrategy {
public:
    uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold); 
};


class MoreIntesePlusStrategy: public AbstractStrategy {
public:
    uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold); 
};


class AverageInteseStrategy: public AbstractStrategy {
public:
    uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold); 
};


class PreferCenterStrategy: public AbstractStrategy {
public:
    uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold); 
};


class PreferRightStrategy: public AbstractStrategy {
public:
    uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold); 
};


class PreferLeftStrategy: public AbstractStrategy {
public:
    uint16_t selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold); 
};


enum StrategyUsed : unsigned char {
    MORE_INTENSE = 0,
    PREFER_CENTER = 1,
    PREFER_RIGHT = 2,
    PREFER_LEFT = 3,
    AVERAGE = 4,
    MORE_INTENSE_PLUS = 5,
};


class StrategySelector {
public:
    static AbstractStrategy * selectStrategy(unsigned char type_strategy);
};



#endif // STRATEGY_H