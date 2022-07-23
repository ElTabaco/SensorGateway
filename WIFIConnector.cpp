#include "WIFIConnector.h"

const char* host      = WIFI_HOST;
const char* ssid      = WIFI_SSID;
const char* password  = WIFI_PASSWORD;

char* setupWiFi(void)
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  //WiFi.persistent(true);
  WiFi.setHostname(host);
  WiFi.begin(ssid, password); //fill in "Your WiFi SSID","Your Password"
  delay(100);

  byte count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 10)
  {
    count ++;
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    return "OK";
  }
  else
  {
    return "FAIL";
  }
}

void reconnectWiFi(void)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
  }
}
