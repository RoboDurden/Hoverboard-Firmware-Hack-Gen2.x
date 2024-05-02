
#define ESP32       // comment out if using Arduino


#ifdef ESP32
  #define oSerialHover Serial1    // ESP32
#else
  #include <SoftwareSerial.h>    
  SoftwareSerial oSerialHover(9,8); // RX, TX 
  #define oSerialHover Serial    // Arduino
#endif

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello Hoverbaord V2.x Autodetect :-)");

  #ifdef ESP32
    // Serial interface, baud, RX GPIO, TX GPIO
    // Note: The GPIO numbers will not necessarily correspond to the
    // pin number printed on the PCB. Refer to your ESP32 documentation for pin to GPIO mappings.
    oSerialHover.begin(19200, SERIAL_8N1, 39, 37);  // Wemos S2 Mini
    //oSerialHover.begin(19200, SERIAL_8N1, 16, 17);  // Wemos Lolin32
      
  #else
    oSerialHover.begin(iBaud);
  #endif
}

unsigned long iTimeTest = 0;
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
    char c = oSerialHover.read();
    if (  (c >= 0x11) && (c <= 0x14)  )
      oSerialHover.write(c);  // send back to hoverboard because MM32 pinFinder that way detects your serial port :-)
    else
      Serial.write(c);   // read it and send it out Serial (USB)
  }
  
  //if (millis() < iTimeTest)
    return;

  iTimeTest = millis() + 1000;
  Serial.println(millis());
}
