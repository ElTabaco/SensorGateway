#include "MQTTConnector.h"


#include "ArduinoJson.h"  // https://arduinojson.org/

const char broker[] = MQTT_BROCKER;
const int  port     = MQTT_PORT;
const char mqttClientId[] = MQTT_CLIENT_ID;
const char mqttUsername[] = MQTT_USER;
const char mqttPassword[] = MQTT_PASSWORD;


WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

char* setupMQTT()
{
  // MQTT Client
  mqttClient.setId(mqttClientId);
  mqttClient.setUsernamePassword(mqttUsername, mqttPassword);
  while (!mqttClient.connect(broker, port)) {
    delay(1000);
  }
  if (!mqttClient.connected()) {
    return "FAIL";
  }
  return "OK";

}

void loopMQTT(void)
{
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();
}
void reconnectMQTT() {
  if (!mqttClient.connected()) {
    while (!mqttClient.connect(broker, port)) {
      delay (1000);
    }
  }
}

void publishMQTT(String package) {
  reconnectMQTT();
  StaticJsonDocument <256> loraBuffer;
  deserializeJson(loraBuffer, package);
  String device          = loraBuffer["device"];
  String topic2  = topic + "/" + device + "/";

  //  unsigned int value          = loraBuffer["distace"]["value"];
  mqttClient.beginMessage(topic2 + "distace/value");
  serializeJson(loraBuffer["distace"]["value"], mqttClient);
  mqttClient.print("mm");
  mqttClient.endMessage();
  /*
    JsonObject documentRoot = loraBuffer.as<JsonObject>();
    for (JsonPair keyValue : documentRoot) {
      mqttClient.beginMessage(topic2 + keyValue.key().c_str());
      serializeJson(loraBuffer[keyValue.key().c_str()], mqttClient);
      //mqttClient.print(packet);
      mqttClient.endMessage();
    }
  */
}


MqttClient getMqttClient()
{
  return mqttClient;
}
