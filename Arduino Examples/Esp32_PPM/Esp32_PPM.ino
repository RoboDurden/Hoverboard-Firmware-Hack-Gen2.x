//    PPM-library: https://github.com/dimag0g/PPM-reader (ArduinoIDE -> PPM_Reader)
//    Tested with Lolin S2 mini + FrSky receiver D4RII in CPPM mode 
//
//    taken from https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/9#issuecomment-1769209126
//
//    10s binary for 2.0 board https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/blob/main/HoverBoardGigaDevice/BinariesToFlash/hoverboard%202.0%20single%20UartBus.bin
//
//    please share feedback to https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x
//
//   if you add steering channel, please send your code to robo@robo4future.de - thanks.

#define ESP32
#define _DEBUG      // debug output to first hardware serial port
//#define DEBUG_RX    // additional hoverboard-rx debug output

#define REMOTE_UARTBUS  // uncomment to connect multiple SINGLE boards to the same UART_BUS

#include "util.h"
#include "hoverserial.h"

#include <PPMReader.h>
byte interruptPin = 3;
byte channelAmount = 4;
PPMReader ppm(interruptPin, channelAmount);
const float a = 0.6; //this is to convert results from channel values (1000lowest-2000max) to -300 to +300 to test
const int b = -900; //this is to convert results from channel values (1000lowest-2000max) to -300 to +300 to test
int result = 0;

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
    delay(2000); // wait some time after reset - to see below message
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

void loop()
{
  unsigned long iNow = millis();
  digitalWrite(LED_BUILTIN, (iNow%2000) < 500);

  //int iSpeed = 3 * (ABS( (int)((iNow/20+100) % 400) - 200) - 100);   // repeats from +300 to -300 to +300 :-)
  //int iSteer = 1 * (ABS( (int)((iNow/400+100) % 400) - 200) - 100);   // repeats from +100 to -100 to +100 :-)
  int iSteer = -100;
  int iSpeed = 0;

  if (iNow > iTimeNextState)
  {
    iTimeNextState = iNow + 3000;
    wState = wState << 1;
    if (wState == 128) wState = 1;  // remove this line to test Shutoff()
  }

//if below uncommented then you can see all channels and values - this code is from example sketch from library PPMReader  
// for (byte channel = 1; channel <= channelAmount; ++channel) {
//        unsigned value = ppm.latestValidChannelValue(channel, 0);
//        Serial.print(value);
//        if(channel < channelAmount) Serial.print('\t');
//  }
//  Serial.println(); 
result = ppm.latestValidChannelValue(3, 0);  //my channel with speed stick on remote is no.3
// beware this is testing only - if RC link is down - result is 0 so it needs to be secured

if (result > 995) 
{
  iSpeed = (result * a) + b;
} 
else 
{
  iSpeed = 0;
  Serial.println("dead RClink"); 
}

//Serial.println("iSpeed="+iSpeed); 
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
      
      HoverSend(oSerialHover,0,iSpeedL,wState);  // hoverboard will answer immediatly on having received this message ...
      delay(10);
      HoverSend(oSerialHover,1,iSpeedR,wState);  // but wait 10 ms for the RX line to be clear again
    }
  #else
    if (bReceived)  // Reply only when you receive data
      HoverSend(oSerialHover,iSteer,iSpeed,wState,wState);
  #endif

}
