/*
  Origin also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/

#include "WIFIConnector.h"
#include "OTAWebUpdater.h"
#include "MQTTConnector.h"
#include "LoraWan.h"

#include "images.h"
String deviceName = "sg_001";      // unique

//#define SENSOR_DHT
#if defined(SENSOR_DHT)
#include "DHT.h"      // https://www.bastelgarage.ch/index.php?route=extension/d_blog_module/post&post_id=1
#define DHTPIN 13
#define DHTTYPE DHT22 // DHT11; DHT22
DHT dht(DHTPIN, DHTTYPE);
#endif

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 5, logo_width, logo_height, logo_bits);
  Heltec.display->display();
}

void displayLoRaData(String package)
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 15, "Received " + getPackSize() + " bytes");
  Heltec.display->drawStringMaxWidth(0, 26, 128, package);
  Heltec.display->drawString(0, 0, getRSSI());
  Heltec.display->display();
}

void setup()
{
  Heltec.display->init();
  // Heltec.display->flipScreenVertically();
  logo();
  delay(1000);

#if defined(SENSOR_DHT)
  dht.begin();
#endif

  Heltec.display->clear();
  String statusLora = setupLora();
  Heltec.display->drawString(0, 30, "Lora..." + statusLora);
  String statusWiFi = setupWiFi();
  Heltec.display->drawString(0, 0, "WIFI..." + statusWiFi);
  String statusOTA = setupOTA(WIFI_HOST);
  Heltec.display->drawString(0, 10, "OTA..." + statusOTA);
  String statusMQTT = setupMQTT();
  Heltec.display->drawString(0, 20, "MQTT..." + statusMQTT);

  Heltec.display->drawString(0, 50, "Wait for incoming data...");
  Heltec.display->display();
}

void loop()
{
  loopMQTT();
  loopOTA();
  if (received())
  {
    String rxPackage = getPackage();
    displayLoRaData(rxPackage);
    reconnectWiFi();
    publishMQTT(rxPackage);
  }

#if defined(SENSOR_DHT) // Update value every 2s
  float h = dht.readHumidity();    // humidity in %
  float t = dht.readTemperature(); // temperature in °C
#endif
  delay(500);
}
