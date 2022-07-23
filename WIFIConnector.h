#ifndef WIFICONNECTOR_H
#define WIFICONNECTOR_H

#include <WiFi.h>

#define WIFI_HOST "LORA_MQTT_Gateway"
#define WIFI_SSID "..."
#define WIFI_PASSWORD "..."

char* setupWiFi(void);
void reconnectWiFi(void);

#endif
