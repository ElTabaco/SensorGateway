/*
  This is a simple example show the Heltec.LoRa recived data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16

  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn

  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/

#include "WIFIConnector.h"
#include "OTAWebUpdater.h"
#include "MQTTConnector.h"
//#include "LoraWan.h"
#include "SensorUltraSonic.h"
#include "ArduinoJson.h"  // https://arduinojson.org/

//#include "images.h"
String deviceName = "sg_001";      // unique


void setup() {
  String statusWiFi = setupWiFi();
  String statusOTA = setupOTA(WIFI_HOST);
  String statusMQTT = setupMQTT();
}

void loop() {
  loopMQTT();
  loopOTA();
  if (received())
  {
    float distance = getDistance();
    StaticJsonDocument <256> loraBuffer;
    loraBuffer["device"] = deviceName;
    loraBuffer["distace"]["value"]   = distance;
    //  loraBuffer["sensor"]["unit"]   = "cm";
    String rxPackage;
    serializeJson(loraBuffer, rxPackage);
    
    String rxPackage = getPackage();
    reconnectWiFi();
    publishMQTT(rxPackage);
  }
  delay(500);
}
