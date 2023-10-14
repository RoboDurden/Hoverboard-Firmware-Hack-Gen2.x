//  SoftwareSerial ist not compatible with this RCReceiver because of interrupt conflicts :-(
//  If you want to have _DEBUG output you need another software serial library or port the RCReceiver to ESP32 which has 3 hardware serial ports
//
//    Tested with Arduino Pro Mini 3.3V and Hoverboard-TX to Arduino-RX and Hoverboard-RX to Arduino TX
//
//    Unplug USB-UART dongle from Arduino to free the RX and TX lines !
//    Unplug Hoverboard-TX to upload Arduino code !
//
//    Only tested with OVERWRITE_PPM as i (Robo Durden) have no rc controller
//
//    PB6 (Hoverboard-TX) and PB7 (Hoverboard-RX) can handle 5V I/O-Level :-)
//
//    Please share feedback to https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x

#define OVERWRITE_PPM   // overwrite ppm values for testing that hoverboard works
//#define _DEBUG      // debug output to first hardware serial port
//#define DEBUG_RX    // additional hoverboard-rx debug output

//#define REMOTE_UARTBUS

#include "util.h"
#include "RCReceiver.h"
#include "hoverserial.h"

#ifdef ESP32
  #error RCReceiver.cpp was written for Arduino interrupts :-/
  #define oSerialHover Serial1    // ESP32
#else
  //#include <SoftwareSerial.h>    // not compatible with RCReceiver because of interrupt conflicts.
  //SoftwareSerial oSerialHover(9,8); // RX, TX 
  #define oSerialHover Serial    // Arduino
#endif

SerialHover2Server oHoverFeedback;

void setup()
{
  #ifdef _DEBUG
    Serial.begin(115200);
    Serial.println("Hello Hoverbaord V2.x :-)");
  #endif
  
  #ifdef ESP32
    HoverSetupEsp32(oSerialHover,19200,39,37);      // baud, rx, tx
  #else
    HoverSetupArduino(oSerialHover,19200);    //  8 Mhz Arduino Mini too slow for 115200 !!!
  #endif

  pinMode(LED_BUILTIN, OUTPUT);
  
  InitRCReceiver(); // Initialize RC receiver
  RCReceiverStart();  // Start RC receiver
}


unsigned long iLast = 0;
void loop()
{
  unsigned long iNow = millis();
  digitalWrite(LED_BUILTIN, (iNow%2000) < 500);
  
  int iSpeed;
  int iSteer;

  uint16_t channel1 = GetRCValue(0);
  uint16_t channel2 = GetRCValue(1);
  uint16_t channel3 = GetRCValue(2);
  float factor = channel3 < 1500 ? 0.5 : 1; // Activate/deactivate speed mode
  iSpeed = CLAMP((float)channel1 * factor, -1000, 1000);
  iSteer = CLAMP(((float)channel2 * 2 ) - 3000.0, -1000, 1000);   // // Value -1000 to 1000
  if (iSpeed < 0) iSteer *= -1;

  #ifdef OVERWRITE_PPM
    // overwrite values for testing that hoverboard works
    iSpeed = 3 * (ABS( (int)((iNow/20+200) % 400) - 200) - 100);   // repeats from +300 to -300 to +300 :-)
    iSteer = 0;
  #endif
    

  boolean bReceived = Receive(oSerialHover,oHoverFeedback);   
  if (bReceived)
  {
    DEBUGT("millis",iNow-iLast);
    DEBUGT("iSpeed",iSpeed);
    DEBUGT("iSteer",iSteer);
    HoverLog(oHoverFeedback);
    iLast = iNow;
   }

  #ifdef REMOTE_UARTBUS
    if (iNow > iNext)
    {
      iNext = iNow + 100;
      //DEBUGLN("time",iNow)
      int iSpeedL = CLAMP(iSpeed + iSteer,-1000,1000);
      int iSpeedR = -CLAMP(iSpeed - iSteer,-1000,1000);
      
      HoverSend(oSerialHover,1,iSpeedL);  // hoverboard will answer immediatly on having received this message ...
      delay(10);
      HoverSend(oSerialHover,2,iSpeedR);  // but wait 10 ms for the RX line to be clear again
    }
  #else
    if (bReceived)  // Reply only when you receive data
      HoverSend(oSerialHover,iSteer,iSpeed);
  #endif
  
}
