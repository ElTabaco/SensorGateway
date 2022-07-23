#ifndef OTAWEBUPDATER_H
#define OTAWEBUPDATER_H

#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

char* setupOTA(const char* host);
void loopOTA(void);

#endif
