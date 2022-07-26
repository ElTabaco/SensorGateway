#include "LoraWan.h"

String package;
String rssi = "RSSI --";
String packSize = "--";
bool receiveflag = false; // software flag for LoRa receiver, received data makes it true.

char* setupLora(void)
{
  // https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/lora/API.md
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, LORA_BAND /*long BAND*/);
  Heltec.display->init();
  //  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  LoRa.setSpreadingFactor(LORA_SF);
  // LoRa.enableCrc();
  LoRa.onReceive(callbackOnReceive);
  // send();
  LoRa.receive();
  return "OK";
}

void send()
{
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.endPacket();
}

void callbackOnReceive(int packetSize) // LoRa receiver interrupt service
{
  // if (packetSize == 0) return;
  package = "";
  packSize = String(packetSize, DEC);

  while (LoRa.available())
  {
    package += (char)LoRa.read();
  }
  rssi = "RSSI: " + String(LoRa.packetRssi(), DEC);
  // RssiDetection = abs(LoRa.packetRssi());

  receiveflag = true;
}

bool received()
{
  return receiveflag;
}

String getPackage()
{
  receiveflag = false;
  LoRa.receive();
  return package;
}

String getPackSize()
{
  return packSize;
}

String getRSSI()
{
  return rssi;
}
