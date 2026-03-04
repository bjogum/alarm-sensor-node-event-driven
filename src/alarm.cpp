#include <stdio.h>
#include "tasks.h"
#include <Arduino.h>
#include "alarm.h"

bool sysAlarming = false;
SystemState sysState = STATE_ARMED_AWAY; // Endast för test: detta state kommer uppdateras ESP32 via BLE.


void checkAlarmStatus(){ 
  switch (sysState)
  {
  case STATE_ARMED_AWAY:
      if (sensorStatus.smokeSensor == true || sensorStatus.fireTemp == true){
        printf("\n--FIRE DETECTED--\n");
      }
      if (sensorStatus.motionDetect == true){
        printf("\n--MOTION DETECTED--\n");
      }
      if (sensorStatus.reedSensor1 == true || sensorStatus.reedSensor2 == true){
        printf("\n--DOOR/WINDOW OPEND!--\n");
      }
      if (sensorStatus.waterLeak == true){
         printf("\n--WATER-LEAK DETECTED--\n");
      }
      if (sensorStatus.indoorHumidity >= 70){       // bara för test
         printf("\n--HIGH HUMIDITY DETECTED--\n");  // bara för test
      }
  break;

  case STATE_ARMED_HOME:
            if (sensorStatus.smokeSensor == true || sensorStatus.fireTemp == true){
        printf("\n--FIRE DETECTED--\n");
      }
      if (sensorStatus.reedSensor1 == true || sensorStatus.reedSensor2 == true){
        printf("\n--DOOR/WINDOW OPEND!--\n");
      }
      if (sensorStatus.waterLeak == true){
         printf("\n--WATER-LEAK DETECTED--\n");
      }
  break;

  case STATE_DISARMED:
      if (sensorStatus.smokeSensor == true || sensorStatus.fireTemp == true){
        printf("\n--FIRE DETECTED--\n");
      }
      if (sensorStatus.waterLeak == true){
         printf("\n--WATER-LEAK DETECTED--\n");
      }
  break;

  }
}