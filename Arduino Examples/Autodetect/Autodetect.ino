
#define ESP32       // comment out if using Arduino

//#define _DEBUG  // uncomment to get additional debug output
#ifdef _DEBUG
  #define OUTC(code) {code}
  #define OUT(s)  {Serial.print(s);}
  #define OUT2T(s,i)  {Serial.print(s);Serial.print(": ");Serial.print(i);Serial.print("  ");}
  #define OUT2TX(s,i)  {Serial.print(s);Serial.print(": ");Serial.print(i,HEX);Serial.print("  ");}
  #define OUT2N(s,i)  {Serial.print(s);Serial.print(": ");Serial.print(i);Serial.println();}
#else
  #define OUTC(code)
  #define OUT(s)
  #define OUT2T(s,i)
  #define OUT2TX(s,i)
  #define OUT2N(s,i)
#endif

// Serial interface, baud, RX GPIO, TX GPIO
// Note: The GPIO numbers will not necessarily correspond to the
// pin number printed on the PCB. Refer to your ESP32 documentation for pin to GPIO mappings.
#define BAUDRATE 19200   // 19200 is default on hoverboard side because Arudino Nano SoftwareSerial can not do 115200
#ifdef ESP32
  const int pinRX = 39, pinTX = 37;   // Wemos S2 Mini
  //const int pinRX = 16, pinTX = 17;    Wemos Lolin32
  #define oSerialHover Serial1    // ESP32
#else
  #include <SoftwareSerial.h>    
  const int pinRX = 9, pinTX = 8;
  SoftwareSerial oSerialHover(pinRX,pinTX); // RX, TX 
  #define oSerialHover Serial    // Arduino
#endif

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello Hoverbaord V2.x Autodetect :-)");

  #ifdef ESP32
    oSerialHover.begin(BAUDRATE, SERIAL_8N1, pinRX,pinTX);
  #else
    oSerialHover.begin(iBaud);
  #endif
}

#define PINS_DETECT 18
const char* asScan[PINS_DETECT] = {"HALL_A","HALL_B","HALL_C","PHASE_A","PHASE_B","PHASE_C","LED_RED","LED_ORANGE","LED_GREEN","UPPER_LED","LOWER_LED","ONBOARD_LED","BUZZER","VBATT","CURRENT_DC","SELF_HOLD","BUTTON","BUTTON_PU"};
uint32_t aiPinScan[PINS_DETECT] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    // the found pins

typedef struct __attribute__((packed, aligned(1))) {
  uint8_t cStart;   //  = '/';
  uint8_t wCmd;
} HeaderData;

enum{  DATA_None, DATA_Request, DATA_Save};
HeaderData oDataHeader = {0x01,DATA_None};  // wenn autodetect.ino receives 0x01 it stores the incoming data or returns it's storage


unsigned long iTimeTest = 0;
int iSerialHoverType = 0;
void loop() 
{
  digitalWrite(LED_BUILTIN, (millis()%2000) < 500);
  if (Serial.available())  // If anything comes in Serial (USB),
  {      
    char c = Serial.read();
    //Serial.println(c );
    oSerialHover.write(c);   // read it and send it to hoverboard
  }

  if (oSerialHover.available())   // If anything comes in from hoverboard
  {     
    if (iSerialHoverType==1)
    {
      int iAvail = oSerialHover.available();
      //OUT2T("iAvail",iAvail)
      if (iAvail < sizeof(HeaderData)-1 +sizeof(aiPinScan))
        return;

      HeaderData oHeaderRx;
      uint32_t aiPinScanRx[PINS_DETECT];
      oSerialHover.readBytes(((uint8_t*)&oHeaderRx)+1, sizeof(oDataHeader)-1);   // 0x01 already read
      oSerialHover.readBytes((uint8_t*)aiPinScanRx, sizeof(aiPinScanRx));
      iSerialHoverType = 0;
        
      OUT2N(oHeaderRx.wCmd,oDataHeader.wCmd)
      if (oHeaderRx.wCmd == DATA_Request)
      {
        oSerialHover.write((uint8_t*) &oDataHeader, sizeof(oDataHeader)); 
        //delay(100);
        oSerialHover.write((uint8_t*) aiPinScan, sizeof(aiPinScan)); 
        OUT2N("DATA_Request",sizeof(oDataHeader)+sizeof(aiPinScan));
      }
      else
      {
        oDataHeader.wCmd = oHeaderRx.wCmd;  // store for later request
        memcpy((uint8_t*)aiPinScan, (uint8_t*)aiPinScanRx, sizeof(aiPinScanRx));
      }
      OUTC(
        #define AHB2_BUS_BASE         ((uint32_t)0x48000000U)        /*!< ahb2 base address                */

        OUT("\npins:\t")
        for (int i=0; i<PINS_DETECT; i++)
        {  
          OUT2T(asScan[i],aiPinScan[i] & ~AHB2_BUS_BASE)
        }
        OUT("\n")
      )
      return;    
    }

    char c = oSerialHover.read();

    // MM32 pinFinder: emulate serial bridge
    if (  (c >= 0x11) && (c <= 0x14)  )
    {
      oSerialHover.write(c);  // send back to hoverboard because MM32 pinFinder that way detects your serial port :-)
      return;
    }
    else if (c == 0x01)  // GD32 autodetect temporary storage
    {
      iSerialHoverType = 1;
      return;
    }
    Serial.write(c);   // read it and send it out Serial (USB)
  }
  if (iTimeTest > millis())
    return;
  iTimeTest = millis() + 1000;
  //Serial.println(millis()); 
}
