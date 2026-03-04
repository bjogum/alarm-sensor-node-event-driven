#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>
#include <stdio.h>

enum SensorState {
    READING_DHT,
    READING_WATER
};

// Struct för all sensor data som samlas in
typedef struct {
    // Alarm (prio 1)
    volatile bool reedSensor1; // volatile: tvingar cpu att läsa variablen från RAM, för att få en 100% korrekt status.
    volatile bool reedSensor2;
    volatile bool motionDetect;

    // Fire (prio 2)
    bool smokeSensor;
    float fireTemp; // over 60c?

    // Enviroment (prio 3)
    float indoorTemp;
    float indoorHumidity;
    bool waterLeak;
}SensorData;

void readPrio3Sensors();

// deklaration av extern sensorStatus
extern SensorData sensorStatus;

#endif