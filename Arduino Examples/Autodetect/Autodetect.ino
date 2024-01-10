
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
  Serial.begin(115200);
  Serial.println("Hello Hoverbaord V2.x Autodetect :-)");

  #ifdef ESP32
    // Serial interface, baud, RX GPIO, TX GPIO
    // Note: The GPIO numbers will not necessarily correspond to the
    // pin number printed on the PCB. Refer to your ESP32 documentation for pin to GPIO mappings.
      oSerialHover.begin(19200, SERIAL_8N1, 39, 37);
  #else
    oSerialHover.begin(iBaud);
  #endif
}

void loop() 
{
  if (Serial.available())  // If anything comes in Serial (USB),
  {      
    oSerialHover.write(Serial.read());   // read it and send it to hoverboard
  }

  if (oSerialHover.available())   // If anything comes in from hoverboard
  {     
    Serial.write(oSerialHover.read());   // read it and send it out Serial (USB)
  }
}
