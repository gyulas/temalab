#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-12-04 01:26:20

#include "Arduino.h"
#include "Arduino.h"
#include "Wire.h"
#include "VL6180X.h"
#include "math.h"
#include "TimerOne.h"
#include "TimerThree.h"
void controllerRun(void) ;
inline void pwmBinary() ;
void linearPWM(uint8_t min, uint8_t max, uint8_t wait) ;
void steppedPWM(uint8_t min, uint8_t max, uint8_t ts, uint8_t burst) ;
void changeReference() ;
void setup() ;
void loop() ;

#include "distanceMeter.ino"


#endif
