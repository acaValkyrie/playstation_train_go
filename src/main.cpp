#include <Arduino.h>
#include "masscon.h"
#include "speed.h"

void setup(){
  massconSetup();
  speedSetup();
}

void loop(){
  updateBrakeAccell();

  updateSpeed();
  int speed = (int)getSpeed();

  analogWrite(pwmOutPin, (int)speed);
  
  printMassconPropaties();
  printSpeed();
}
