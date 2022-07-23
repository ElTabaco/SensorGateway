#ifndef LORAWAN_H
#define LORAWAN_H

#include "heltec.h"

// LORA
#define LORA_BAND    868E6  //you can set band here directly,e.g. 868E6,915E6, 433E6
#define LORA_SF     7  // 6 - 12. spreading factor of 6, implicit header mode must be used to transmit and receive packets.

char* setupLora(void);

void callbackOnReceive(int packetSize);

bool received();

String getPackage();

String getPackSize();

String getRSSI();

#endif
