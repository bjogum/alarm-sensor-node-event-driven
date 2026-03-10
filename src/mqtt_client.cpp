#include "alarm.h"
#include "mqtt_client.h"
#include "wifi_manager.h"
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>

#define MQTT_BROKER "192.168.1.101"
#define MQTT_PORT 1883
#define MQTT_SEND_TIME_INTERVALL 2000 // skicka MQTT varannan sekund

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = MQTT_BROKER;
int port = MQTT_PORT;
const char indoorTempTopic[]     = "sensor/indoorTemp";
const char indoorHumidTopic[]    = "sensor/indoorHumidity";
const char waterleakTopic[]      = "sensor/waterleak";
const char fireTopic[]           = "sensor/fire";
const char systemFailure[]       = "systemFailure";

//bool tryMQTTconnect = false;
unsigned long MQTTConnectTimer = 0;
unsigned long MQTTLastSendTimer = 0;

// funktionen håller igång MQTT samt skickar/ta emot meddelanden.
bool manageMQTT() {
    // d) LWT: Maxtid, 10s offline -> ESP ger larm 
    // skriv testamentet här...
    

    // om det gått 2 sek sen connect & nu conencted, skicka init
    if ((node.sysTime - MQTTConnectTimer >= 2000) && (!node.connectionStatus.mqttIsActive)){
        MQTTConnectTimer = node.sysTime;

        if (mqttClient.connect(broker, port)) {
            node.connectionStatus.mqttIsActive = true;
            initSendMQTT();
            return true;

        } else {
            node.connectionStatus.mqttIsActive = false;
            Serial.println("<< MQTT : Connect error >> Test in 2 sec");
            return false;
        }
    }

}

void initSendMQTT(){
        // one-time, init messages
    }

// -- avgör om datan behöver publiseras - Beroende på sensorer/status samt state --
void sendMQTT(){
    // .poll() : håller igång anslutningen (ping) - och skickar/tar emot MQTT
    mqttClient.poll();

    if (node.sysTime - MQTTLastSendTimer >= MQTT_SEND_TIME_INTERVALL){
        MQTTLastSendTimer = node.sysTime;
        mqttClient.beginMessage(indoorTempTopic);
        mqttClient.print(node.sensors.indoorTemp);
        if (mqttClient.endMessage()) {
            Serial.println("Temp: Sent OK!");
        }

        mqttClient.beginMessage(indoorHumidTopic);
        mqttClient.print(node.sensors.indoorHumidity);
        if (mqttClient.endMessage()) {
            Serial.println("Humidity: Sent OK!");
        }

        if (node.alarmStatus.fireAlarm){
            mqttClient.beginMessage(fireTopic);
            mqttClient.print(node.sensors.fireTemp);
            mqttClient.print(node.sensors.smokeSensor);
            if (mqttClient.endMessage()) {
                Serial.println("Fire: Sent OK!");
        }
    }

        if (node.alarmStatus.waterLeak){
            mqttClient.beginMessage(waterleakTopic);
            mqttClient.print(node.sensors.waterLeak);
            if (mqttClient.endMessage()) {
                Serial.println("Water: Sent OK!");
            }
        }

        if (node.alarmStatus.systemFailure){
            // skicka releveant larm
        }
    }
        // c) skicka heartbeat var 30e sek (bra trots LWT)
}

void receiveMQTT(){


    // TA EMOT data (sub) från ESP -> "state"
}