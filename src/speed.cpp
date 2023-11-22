#include "speed.h"

float speed;

void speedSetup(){
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

void updateSpeed(){
  speed += calcDeltaSpeed();
}

float getSpeed(){
  return speed;
}

void printSpeed(){
  Serial.print(", speed:");
  Serial.println(speed);          //速度表示
}
