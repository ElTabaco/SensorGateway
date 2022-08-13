/*
  Origin also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/

#include "WIFIConnector.h"
#include "OTAWebUpdater.h"
#include "MQTTConnector.h"
//#include "LoraWan.h"
#include "SensorUltraSonic.h"
#include "ArduinoJson.h"  // https://arduinojson.org/
String deviceName = "sg_001";      // unique
//#define SENSOR_DHT
#if defined(SENSOR_DHT)
#include "DHT.h"      // https://www.bastelgarage.ch/index.php?route=extension/d_blog_module/post&post_id=1
#define DHTPIN 13
#define DHTTYPE DHT22 // DHT11; DHT22
DHT dht(DHTPIN, DHTTYPE);
#endif

void setup()
{
  //String statusWiFi = setupWiFi();
  //String statusOTA = setupOTA(WIFI_HOST);
  //String statusMQTT = setupMQTT();
  setupUltraSonic();
  Serial.begin(115200);
#if defined(SENSOR_DHT)
  dht.begin();
#endif

}

void loop()
{
  Serial.print("############# Debug");
  //loopMQTT();
  //loopOTA();
  float distance = getDistance();
  Serial.printf("Distance is %f\n", distance);
  //StaticJsonDocument <256> loraBuffer;
  //loraBuffer["device"] = deviceName;
  //loraBuffer["distace"]["value"]   = distance;
  //  loraBuffer["sensor"]["unit"]   = "cm";
  //String rxPackage;

#if defined(SENSOR_DHT) // Update value every 2s
  float h = dht.readHumidity();    // humidity in %
  float t = dht.readTemperature(); // temperature in °C
#endif
  delay(500);
}
