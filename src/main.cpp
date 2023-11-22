#include <Arduino.h>
#include "masscon.h"

#define pwmOutPin 3

float speed;

void setup(){
  massconSetup();
  pinMode(pwmOutPin, OUTPUT);
  speed = 0;
}

float calcDeltaSpeed(){
  int P = getP();
  int B = getB();
  float _deltaSpeed = P * 0.1 - B * 0.1;
  if(_deltaSpeed > 255){
    _deltaSpeed = 255;
  }else if(_deltaSpeed < 0){
    _deltaSpeed = 0;
  }
  return _deltaSpeed;
}

void printSpeed(){
  Serial.print(", speed:");
  Serial.println(speed);          //速度表示
}


void loop(){
  updateBrakeAccell();
  speed += calcDeltaSpeed();
  analogWrite(pwmOutPin, (int)speed);
  printMassconPropaties();
  printSpeed();
}
