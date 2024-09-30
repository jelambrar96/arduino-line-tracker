#include "strategy.h"


uint16_t MoreInteseStrategy::selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) {
    uint16_t max_value = 0;
    unsigned char position = 0;
    for (unsigned char i = 0; i < numSensors; ++i) {
        if (sensorValues[i] > max_value) {
            max_value = sensorValues[i];
            position = i;
        }
    }
    uint16_t salida = position * 1000;
    return salida;
}


uint16_t MoreIntesePlusStrategy::selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) {
    uint16_t max_value = 0;
    unsigned char position = 0;
    for (unsigned char i = 0; i < numSensors; ++i) {
        if (sensorValues[i] > max_value) {
            max_value = sensorValues[i];
            position = i;
        }
    }
    uint16_t salida = position * 1000;
    return salida;
}


uint16_t AverageInteseStrategy::selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) {
    uint32_t sum1 = 0;
    uint32_t sum2 = 0;
    for (unsigned char i = 0; i < numSensors; ++i) {
        if (sensorValues[i] < threshold) { 
            continue;
        }
        sum1 += sensorValues[i] * i;
        sum2 += sensorValues[i];
    }
    uint16_t salida = sum1 * 1000 / sum2;
    return salida;
}


uint16_t PreferCenterStrategy::selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) {
    unsigned char center_position = numSensors / 2;
    unsigned char square_position = 255;
    unsigned char position = 0;
    for (unsigned char i = 0; i < numSensors; ++i) {
        if (sensorValues[i] < threshold) { 
            continue;
        }
        unsigned char temp_square_position;
        if (i <= center_position) {
            temp_square_position = i - center_position;
        }
        else {
            temp_square_position = center_position - i;
        }
        temp_square_position *= temp_square_position;
        if (temp_square_position < square_position) {
            square_position = temp_square_position;
            position = i;
        }
    }
    uint16_t salida = position * 1000;
    return salida;    
}

uint16_t PreferRightStrategy::selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) {
    uint16_t max_value = 0;
    unsigned char position = 0;
    for (unsigned char i = 0; i < numSensors; ++i) {
        if (sensorValues[i] >= threshold) { 
            return i;
        }
        if (sensorValues[i] > max_value) {
            max_value = sensorValues[i];
            position = i;
        }
    }
    uint16_t salida = position * 1000;
    return salida;
}

uint16_t PreferLeftStrategy::selectPosition(uint16_t * sensorValues, unsigned char numSensors, uint16_t threshold) {
    uint16_t max_value = 0;
    unsigned char position = 0;
    for (unsigned char i = numSensors - 1; i <= 0; --i) {
        if (sensorValues[i] >= threshold) { 
            return i;
        }
        if (sensorValues[i] > max_value) {
            max_value = sensorValues[i];
            position = i;
        }
    }
    uint16_t salida = position * 1000;
    return salida;
}

AbstractStrategy * StrategySelector::selectStrategy(unsigned char type_of_strategy) {
    switch (type_of_strategy) {
    case StrategyUsed::MORE_INTENSE:
        return new MoreInteseStrategy();
        break;
    case StrategyUsed::PREFER_CENTER:
        return new PreferCenterStrategy();
        break;
    case StrategyUsed::PREFER_LEFT:
        return new PreferLeftStrategy();
        break;
    case StrategyUsed::PREFER_RIGHT:
        return new PreferRightStrategy();
        break;
    case StrategyUsed::AVERAGE:
        return new AverageInteseStrategy();
        break;
    case StrategyUsed::MORE_INTENSE_PLUS:
        return new MoreIntesePlusStrategy();
        break;
    default:
        nullptr;
    }
}


