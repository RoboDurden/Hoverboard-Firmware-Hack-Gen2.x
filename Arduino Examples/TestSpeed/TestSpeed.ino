//    Tested with Arduino Pro Mini 3.3V and Hoverboard-TX to pin 9 and Hoverboard-RX to pin 8
//
//    PB6 (Hoverboard-TX) and PB7 (Hoverboard-RX) can handle 5V I/O-Level :-)
//
//    please share feedback to https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x


#define _DEBUG      // debug output to first hardware serial port
//#define DEBUG_RX    // additional hoverboard-rx debug output
//#define REMOTE_UARTBUS

#include "util.h"
#include "hoverserial.h"

#ifdef ESP32
  #define oSerialHover Serial1    // ESP32
#else
  #include <SoftwareSerial.h>    // not compatible with RCReceiver because of interrupt conflicts.
  SoftwareSerial oSerialHover(9,8); // RX, TX 
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

  //pinMode(39, OUTPUT);
  //pinMode(37, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long iLast = 0;
unsigned long iNext = 0;
unsigned long iTimeNextState = 3000;
uint8_t  wState = 1;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff

void loop()
{
  unsigned long iNow = millis();
  digitalWrite(LED_BUILTIN, (iNow%2000) < 500);
  //digitalWrite(39, (iNow%500) < 250);
  //digitalWrite(37, (iNow%500) < 100);

  int iSpeed = 3 * (ABS( (int)((iNow/20+100) % 400) - 200) - 100);   // repeats from +300 to -300 to +300 :-)
  int iSteer = 1 * (ABS( (int)((iNow/400+100) % 400) - 200) - 100);   // repeats from +100 to -100 to +100 :-)
  //int iSteer = 0;
  //iSpeed /= 10;
  //iSpeed = -300;
  //iSpeed = iSteer = 0;

  if (iNow > iTimeNextState)
  {
    iTimeNextState = iNow + 3000;
    wState = wState << 1;
    if (wState == 64) wState = 1;  // remove this line to test Shutoff = 128
  }
  
  boolean bReceived = Receive(oSerialHover,oHoverFeedback);   
  if (bReceived)
  {
    DEBUGT("millis",iNow-iLast);
    DEBUGT("iSpeed",iSpeed);
    //DEBUGT("iSteer",iSteer);
    HoverLog(oHoverFeedback);
    iLast = iNow;
   }

    if (iNow > iNext)
    {
      iNext = iNow + 100;
      //DEBUGLN("time",iNow)
      int iSpeedL = CLAMP(iSpeed + iSteer,-1000,1000);
      int iSpeedR = -CLAMP(iSpeed - iSteer,-1000,1000);
      
      #ifdef REMOTE_UARTBUS
        HoverSend(oSerialHover,0,iSpeedL,wState);  // hoverboard will answer immediatly on having received this message ...
        delay(10);
        HoverSend(oSerialHover,1,iSpeedR,wState);  // but wait 10 ms for the RX line to be clear again
      #else
        HoverSend(oSerialHover,iSteer,iSpeed,wState,wState);
    #endif
    }
    //if (bReceived)  // Reply only when you receive data

}
