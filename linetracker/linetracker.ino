#include <Servo.h>

#include "QTRSensors.h"
#include "controler.h"

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             9  // emitter is controlled by digital pin 2

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {7, 6, 5, 4, 3, 2, 1, 0}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];
int weights_average[] = {-7, -5, -3, -1, 1, 3, 5, 7};

PServoControler servo_controler;
Servo myservo;


void setup() {

    delay(500);
    pinMode(13, OUTPUT);
    myservo.attach(10);

    // make the calibration take about 10 seconds
    // turn on Arduino's LED to indicate we are in calibration mode
    digitalWrite(13, HIGH);
    for (int i = 0; i < 400; i++) {
        qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
    }
    digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

    // print the calibration minimum values measured when emitters were on
    Serial.begin(9600);
    for (int i = 0; i < NUM_SENSORS; i++) {
        Serial.print(qtra.calibratedMinimumOn[i]);
        Serial.print(' ');
    }
    Serial.println();
  
    // print the calibration maximum values measured when emitters were on
    for (int i = 0; i < NUM_SENSORS; i++) {
        Serial.print(qtra.calibratedMaximumOn[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}


void loop() {
    unsigned int position = qtra.readLine(sensorValues);
    
    // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
    // 1000 means minimum reflectance, followed by the line position

    unsigned int max_sensor_values = 0;
    unsigned char max_sensor_position = 0;
    int sumatoria = 0;
    for (unsigned char i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] > max_sensor_values) {
            max_sensor_position = 0;
            max_sensor_position = sensorValues[i];
        }
        sumatoria += weights_average[i] * sensorValues[i];
        // Serial.print(sensorValues[i]);
        // Serial.print('\t');
    }
    //Serial.println(); // uncomment this line if you are using raw values
    Serial.println(position); // comment this line out if you are using raw values
    
    int angulo_salida = servo_controler.control(sumatoria, 0, 0);
    unsigned char angulo_servo = angulo_salida + 90;

    myservo.write(angulo_servo);

}


