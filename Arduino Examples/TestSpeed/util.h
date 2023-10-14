#ifndef UTIL_H
#define UTIL_H

#define ABS(a) (((a) < 0.0) ? -(a) : (a))
#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define MAP(x, xMin, xMax, yMin, yMax) ((x - xMin) * (yMax - yMin) / (xMax - xMin) + yMin)


#ifdef _DEBUG
  #define DEBUG(txt, val) {Serial.print(F(txt)); Serial.print(F(": ")); Serial.print(val);}
  #define DEBUGT(txt, val) {Serial.print(F(txt)); Serial.print(F(": ")); Serial.print(val); Serial.print(F("\t"));}
  #define DEBUGTX(txt, val) {Serial.print(F(txt)); Serial.print(F(": ")); Serial.print(val,HEX); Serial.print(F("\t"));}
  #define DEBUGTB(txt, val) {Serial.print(F(txt)); Serial.print(F(": ")); Serial.print(val,BIN); Serial.print(F("\t"));}
  #define DEBUGN(txt, val) {Serial.print(F(txt)); Serial.print(F(": ")); Serial.println(val);}
#else
  #define DEBUG(txt, val)
  #define DEBUGT(txt, val)
  #define DEBUGTX(txt, val)
  #define DEBUGTB(txt, val)
  #define DEBUGN(txt, val)
#endif

#endif // UTIL_H
