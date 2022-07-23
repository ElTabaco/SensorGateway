#ifndef MQTTCONNECTOR_H
#define MQTTCONNECTOR_H

#include "WIFIConnector.h"
#include <ArduinoMqttClient.h>

//MQTT-Broker secrets
#define MQTT_USER "..."
#define MQTT_PASSWORD "..." //Username and password for your MQTT-Broker

//MQTT-Broker config
#define MQTT_BROCKER  "192.168.0.2"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "LORA_MQTT_Gateway" //The MQTT Client ID

const String topic  = "lora";

char* setupMQTT(void);
void loopMQTT(void);
void publishMQTT(String package);

#endif
