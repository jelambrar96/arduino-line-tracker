#include <Arduino.h>
#include "QTRSensors.h"
#include "motors.h"
#include "strategy.h"


#define IMPOSIBLE_UINT16_T 65535
#define USE_MONITOR_SERIAL 0
#define DEBUG_MODE 0

const unsigned char EMITTER_PIN = 2; 
const unsigned char STRATEGY_USED = StrategyUsed::MORE_INTENSE_PLUS;


QTRSensors qtr;

const uint8_t SENSOR_COUNT = 7;
uint16_t sensorValues[SENSOR_COUNT];


const unsigned char enB = 5;  
const unsigned char in3 = 9;   //490.20 Frecuencia del pin
const unsigned char in4 = 10;  //490.20 Frecuencia del pin
Motor motorLeft(enB, in3, in4);

const unsigned char enA = 6;  
const unsigned char in1 = 3;  //490.20 Frecuencia del pin
const unsigned char in2 = 11;  //490.20 Frecuencia del pin
Motor motorRight(enA, in1, in2);

const unsigned char BASE_SPEED = 160;
const unsigned char BASE_SPEED_LEFT = 160;
const unsigned char BASE_SPEED_RIGHT = 160;
const unsigned char MAX_SPEED = 254;
const unsigned char MIN_SPEED = 5;

AbstractStrategy * strategy;

uint16_t last_position_selected = IMPOSIBLE_UINT16_T; // imposible value


void setup() {

    // configure the sensors
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6}, SENSOR_COUNT);
    qtr.setEmitterPin(EMITTER_PIN);

    delay(500);
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

    // analogRead() takes about 0.1 ms on an AVR.
    // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
    // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
    // Call calibrate() 400 times to make calibration take about 10 seconds.
    for (uint16_t i = 0; i < 400; i++) {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

#if USE_MONITOR_SERIAL

    // print the calibration minimum values measured when emitters were on
    Serial.begin(9600);
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    // print the calibration maximum values measured when emitters were on
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();

#endif
    
    delay(500);

    strategy = StrategySelector::selectStrategy(STRATEGY_USED);
    delay(500);

    motorLeft.stop();
    motorRight.stop();
    motorLeft.setSpeed(BASE_SPEED);
    motorRight.setSpeed(BASE_SPEED);

    delay(500);

}


void loop() {

    uint16_t position = qtr.readLineBlack(sensorValues);
    uint16_t position_selected = strategy->selectPosition(sensorValues, SENSOR_COUNT, 0);

#if USE_MONITOR_SERIAL
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        Serial.print(sensorValues[i]);
        Serial.print('\t');
    }
    Serial.println("");
    Serial.print("position: ");    
    Serial.println(position);
    Serial.print("position_selected: ");    
    Serial.println(position_selected);
#endif

    if (last_position_selected == IMPOSIBLE_UINT16_T) {
        last_position_selected = position_selected;
    }

    float P = (float)position_selected - 3000;  /// ERROR
    float D = (P - last_position_selected);  /// ERROR MENOS EL ERROR ANTERIOR, DERIVATIVO
    float I = (P + last_position_selected);  /// INTEGRAL

    const float K_P = 0.1000;
    const float K_D = 0.0000; // 0.5900;
    const float K_I = 0.0000;
    float pid_speed = (P * K_P) + (D * K_D) + (I * K_I);
    last_position_selected = position_selected;

    // VELOCIDAMAX la velocidad que alcanza en rectas
    /*
    if (pid_speed > MAX_SPEED) {
        pid_speed = MAX_SPEED;
    }
    if (pid_speed < -1 * MAX_SPEED) {
        pid_speed = -1 * MAX_SPEED;
    }
    */
    float lspeed = BASE_SPEED - pid_speed;
    if (lspeed > MAX_SPEED) {
        lspeed = MAX_SPEED;
    }
    if (lspeed < 0) {
        lspeed = 0;
    } 
    float rspeed = BASE_SPEED + pid_speed;
    if (rspeed > MAX_SPEED) {
        rspeed = MAX_SPEED;
    }
    if (rspeed < 0) {
        rspeed = 0;
    }

    motorRight.setSpeed((unsigned char)rspeed);
    motorLeft.setSpeed((unsigned char)lspeed);
    motorLeft.backward();
    motorRight.forward();

    /*
    if (P > 1600) {
        motorLeft.stop();
        motorRight.stop();
        motorRight.setSpeed(180);
        motorLeft.setSpeed(255);
        motorLeft.forward();
        motorRight.forward();
    }
    if (P < -1600) {
        motorLeft.stop();
        motorRight.stop();
        motorLeft.setSpeed(180);
        motorRight.setSpeed(255);
        motorLeft.backward();
        motorRight.backward();
    }
    */

#if USE_MONITOR_SERIAL
    Serial.print("P: ");
    Serial.println(P);
    Serial.print("I: ");
    Serial.println(I);
    Serial.print("D: ");
    Serial.println(D);
    Serial.print("pid_speed: ");
    Serial.println(pid_speed);
    Serial.print("lspeed: ");
    Serial.println(lspeed);
    Serial.print("rspeed: ");
    Serial.println(rspeed);
#endif

#if DEBUG_MODE
    delay(250);
#endif

}
