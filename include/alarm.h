#ifndef ALARM_H
#define ALARM_H

void checkAlarmStatus();


// enum: definierar systemets "state"
typedef enum
{
    STATE_DISARMED,
    STATE_ARMED_HOME,
    STATE_ARMED_AWAY
}SystemState;

typedef enum
{
    // SecurityTriggerd 
    // SafteyTriggerd
    // SystemFailure
}AlarmReason;


extern SystemState sysState;


extern bool sysAlarming;

#endif