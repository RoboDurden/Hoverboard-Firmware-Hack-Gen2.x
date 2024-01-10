//    Tested with Arduino Pro Mini 3.3V and Hoverboard-TX to pin 9 and Hoverboard-RX to pin 8
//
//    PB6 (Hoverboard-TX) and PB7 (Hoverboard-RX) can handle 5V I/O-Level :-)
//
//    please share feedback to https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x


#define _DEBUG      // debug output to first hardware serial port
//#define DEBUG_RX    // additional hoverboard-rx debug output

#define REMOTE_UARTBUS 
//#define SEND2SINGLES  // uncomment this line if you want to send to two master that then will control their slaves

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

  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long iLast = 0;
unsigned long iNext = 0;
unsigned long iTimeNextState = 3000;
uint8_t  wState = 1;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff

uint8_t  iSendId = 0;
//int aiSpeed[4];


void loop()
{
  unsigned long iNow = millis();
  digitalWrite(LED_BUILTIN, (iNow%2000) < 500);

  int iSpeed = 3 * (ABS( (int)((iNow/20+100) % 400) - 200) - 100);   // repeats from +300 to -300 to +300 :-)
  int iSteer = 1 * (ABS( (int)((iNow/400+100) % 400) - 200) - 100);   // repeats from +100 to -100 to +100 :-)
  //int iSteer = 0;
  //iSpeed /= 10;
  //iSpeed = 500;
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
    //DEBUGT("millis",iNow-iLast);
    DEBUGT("time",iNow);
    //DEBUGT("iSpeed",iSpeed);
    DEBUGT("rx left",oSerialHover.available())
    //while(oSerialHover.available()) oSerialHover.read();
    //DEBUGT("iSteer",iSteer);
    HoverLog(oHoverFeedback);
    iLast = iNow;
   }

  if (iNow < iNext)
    return;

  iNext = iNow + 25;
  //DEBUGLN("time",iNow)

  #ifdef SEND2SINGLES
    int iSpeedL = CLAMP(iSpeed + iSteer,-1000,1000);
    int iSpeedR = -CLAMP(iSpeed - iSteer,-1000,1000);
  
    SerialServer2Hover oMotor;
    oMotor.iSlave = iSendId;
    switch(iSendId++)
    {
    case 0: // front left;
      oMotor.iSpeed = iSpeedL;
      break;
    case 1: // front right;
      oMotor.iSpeed = iSpeedR;
      break;
    case 2: // rear left;
      oMotor.iSpeed = iSpeedL;
      break;
    case 3: // rear Right;
      oMotor.iSpeed = iSpeedR;
      iSendId = 0;
      break;
    }
    oMotor.wState = wState;
    
    //DEBUGT("time",iNow)  DEBUGN("HoverSend to",iSendId);
    HoverSendData(oSerialHover,oMotor);  // hoverboard will answer immediatly on having received this message ...
    //HoverSend(oSerialHover,iSendId,aiSpeed[iSendId],wState);  // hoverboard will answer immediatly on having received this message ...
  #else
    SerialServer2HoverMaster oMaster;
    oMaster.iSlave = iSendId;
    switch(iSendId++)
    {
    case 0: // front axis
      oMaster.iSpeed = iSpeed;
      oMaster.iSteer = iSteer;
      break;
    case 1: // rear axis;
      oMaster.iSpeed = iSpeed;
      oMaster.iSteer = iSteer;
      iSendId = 0;
      break;
    }
    oMaster.wState = wState;    // turn on off some led and shutoff master+slave
    oMaster.wStateSlave = wState; // turn on off some led 
    
    //DEBUGT("time",iNow)  DEBUGN("HoverSend to",iSendId);
    HoverSendData(oSerialHover,oMaster);  // hoverboard will answer immediatly on having received this message ...
  #endif
}
