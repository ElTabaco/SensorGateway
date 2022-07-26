

#include "SensorUltraSonic.h"
// JSN SR04T 2.0 ultrasound module
#define ULTASONIC_MODE3

#if defined(ULTASONIC_MODE1)
#define TRIGGER_PIN   (13) //RX_PIN / TRIGGER_PIN Module pins 
#define ECHO_PIN      (12) //TX_PIN / ECHO_PIN Module pins 
#elif defined(ULTASONIC_MODE3)
#include <SoftwareSerial.h>
#define RX_PIN    (16) //RX_PIN / TRIGGER_PIN Module pins 
#define TX_PIN    (17) //TX_PIN / ECHO_PIN Module pins 
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
#endif

void setupUltraSonic()
{
#if defined(ULTASONIC_MODE1)
  pinMode(TRIGGER_PIN  , OUTPUT);
  pinMode(ECHO_PIN  , INPUT);   // INPUT_PULLUP
#elif defined(ULTASONIC_MODE3)
  mySerial.begin(9600);
#endif
}

#if defined(ULTASONIC_MODE1)
float getDistance() {
  digitalWrite(TRIGGER_PIN  , LOW); // Set the TRIGGER_PIN  ger pin to low for 2uS
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN  , HIGH); // Send a 10uS high to TRIGGER_PIN  ger ranging
  delayMicroseconds(20);

  digitalWrite(TRIGGER_PIN  , LOW); // Send pin low again
  int duration = pulseIn(ECHO_PIN, HIGH); // Read in times pulse
  float distanceTemp = duration * 0.343 / 2; //Convert the pulse duration to distance. Speed of sound wave devided by 2 (go and back) (alternativ devide with 58.2)
  return distanceTemp;
}
#elif defined(ULTASONIC_MODE3)
float getDistance() {
  // Mode 2 JSN SR04 T ultrasound module
  int counter = counter + 1;

  while (counter < 20)  {
    //mySerial.write(0x55);
    if (mySerial.available()) {
      byte startByte, h_data, l_data, sum = 0;
      byte buf[3];

      startByte = (byte)mySerial.read();
      if (startByte == 0xFF) {
        mySerial.readBytes(buf, 3);
        h_data = buf[0];
        l_data = buf[1];
        sum = buf[2];
        mySerial.flush();
        if (((startByte + h_data + l_data) & 0xFF) == sum) {
          float distanceTemp = (h_data << 8) + l_data;
          //mySerial.flush();
          return distanceTemp;
        }
        // return 333333;
      }
    }
    delay(1000);
  }// while (startByte == 0xff);
  return 222222;
}
#else
float getDistance() {
  return 999999;
} 
#endif
